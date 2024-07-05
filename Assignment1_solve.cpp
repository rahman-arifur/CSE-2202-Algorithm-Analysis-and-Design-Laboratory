// Name  : Md. Arifur Rahman
// Roll  : 2107062
// Group : B1


// use c++ 17 or latter

#include "iostream" // for cin, cout
#include "vector" // for a dynamic array


using namespace std; // to use the standard library's functionalities


const int INF = 1e9 + 7;

// every thing is 0 based indexing
class minHeap{

private:
    vector<pair<int, int>> heap; // for storing the key-value pair
    // pair.first = weight / value and pair.second = node

    int _size = 0; // for keeping track of empty heap
public:
    bool is_empty(); // O(1)

    // its better if this function is inline
    int parent(int index) { // returning the parent of an index
        return (index - 1) >> 1; // bitwise is faster 
    }// O(1)

    void minHeapifyDown(int index); // O(log n)
    pair<int, int> extract_min(); // O(log n)
    void minHeapifyUp(int index); // O(log n)
    void insert(int key,int value); // O(log n)
    void printHeap(); // O(n)
    void decrease_key(int key, int new_value); // O(n)
};

void minHeap :: decrease_key(int key, int new_value) {
    for(auto& [value, node] : heap) 
        if(node == key) // if key is found then 
            return void(value = new_value); // assingning new valu
}


bool minHeap :: is_empty() { // checks if the heap is empty
        return _size <= 0;
}

void minHeap::printHeap() {
    cout << "The min heap is currently stored in this order:\n";
    cout << "Weight  Node\n";
    for(auto& [weight, node] : heap)
        cout << "[" << weight << ", " << node << "]\n";
}

void minHeap :: insert(int key,int value) { // inserting a key-value pair into the heap
    heap.push_back({value, key}); // will sort using the weight/value not the key
    _size++; 
    minHeapifyUp(_size - 1); // placing the inserted pair under a minimum parent
}

void minHeap :: minHeapifyUp(int index) {
    while(
        index > 0 and 
            heap[ parent(index) ].first > heap[ index ].first
        ) { // as long as the parent of a node has larger weight than the node, will keep swapping the parent with the child
        swap(heap[ parent(index) ], heap[ index ]);
        index = parent(index);
    }
}

pair<int, int> minHeap :: extract_min() {
    
    pair<int, int> minimum = heap[0];
    swap(heap[0], heap[_size - 1]); // swapping with last so that we can delete the element in O(1) time
    heap.pop_back(); // popping the minimum element O(1)
    _size--;
    // cout << "pop\n";
    if(_size > 0)
        minHeapifyDown(0); // taking the first node to its proper parent < node
    
    swap(minimum.first, minimum.second); // making the value-key into a key-value pair
    return minimum;
}

void minHeap :: minHeapifyDown(int index) {
    int small, left, right;
    while(true) {
        small = index;
        left = (index << 1) + 1; // 2 * node + 1
        right = left + 1; // 2 * node + 2

        if(left < _size and heap[left].first < heap[small].first)
                small = left;
        
        if(right < _size and heap[right].first < heap[small].first)
                small = right;
        
        if(small == index) break; // meaning the parent is smaller than both its child

        swap(heap[index], heap[small]); // will swap the pare
        index = small;
    }
}



class Dijkstra {
private:
    // to print out the distance array after operation
    void printDistance(const int& vertices,const  vector<int>& distance);
    
public: 
    // taking the source node, graph and number of vertices as parameters to determine the shortest path
    void shortestPath(const int& source, vector<pair<int, int>> adjList[], const int& V);
};

void Dijkstra :: shortestPath(const int& source, vector<pair<int, int>> adjList[], const int& V) {
    auto distance = vector<int> (V, INF); // distance array marked all infinty 
    distance[source] = 0; // start node distance is 0
    minHeap smallDis; // minheap to always get smallest wieghted node till now
    smallDis.insert(source, 0);
    while(!smallDis.is_empty()) {
        auto [key, value] = smallDis.extract_min();
        if(distance[key] < value) continue; // if processed already then skip
        // cout << key << " " << value << "\n";
        for(auto& [endNode, cost] : adjList[key]) {
            if(distance[endNode] > distance[key] + cost) { // if the current distance of the destination is greater than weight plus its predecessor nodes destination...
                distance[endNode] = distance[key] + cost; // then update the distance as minimum = path relaxation
                smallDis.insert(endNode, distance[endNode]); // then we push it in the queue to process later
            }
        }
    }
    printDistance(V, distance);
}

void Dijkstra :: printDistance(const int& vertices, const vector<int>& distance) {
    for(int i = 0; i < vertices; ++i) {
        cout << "Vertex " << i << ": Distance ";
        if(INF <= distance[i]) cout << "infinity";
        else cout << distance[i];
        cout << "\n";
    }
}


int main() {
    int V, E;
    cin >> V >> E; // vertices, edges
    vector<pair<int, int>> adjList[V]; // adjoint list representation of graph
    int from, to, weight;
    for(int i = 0; i < E; ++i) {
        cin >> from >> to >> weight;
        adjList[from].push_back({to, weight}); // storing pair as node - weight
        adjList[to].push_back({from, weight});
    }
    Dijkstra solver;
    int source = 0;
    // for sources other than 0 uncomment the next line
    // cin >> source;
    solver.shortestPath(source, adjList, V);
    // minHeap x;
    // x.insert(1, 2);
    // x.insert(1, 1);
    // x.insert(1, 0);
    // x.extract_min();
    // x.insert(1, -1);
    // x.printHeap();
return 0;
}
