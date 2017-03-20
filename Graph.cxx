#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	Edge(int vertex1, int vertex2){ v1 = vertex1; v2 = vertex2; }
	int v1;
	int v2;
};

struct Graph {
	Graph(int vs) {
		numOfVertices = vs;
		distanceMatrix.resize(vs);
		adjacencyMatrix.resize(vs);
		for(int i = 0; i < vs; i++) {
			distanceMatrix[i].resize(vs);
			fill(distanceMatrix[i].begin(), distanceMatrix[i].end(), -1);
			adjacencyMatrix[i].resize(vs);
			fill(adjacencyMatrix[i].begin(), adjacencyMatrix[i].end(), 0);
		}
	}
	int numOfVertices;
	vector<Edge> edges;
	vector< vector<int> > distanceMatrix;
	vector< vector<int> > adjacencyMatrix;
};

// This will fill out the whole row for the given vertex
void BFS(Graph *g, int v) {
	g->distanceMatrix[v][v] = 0;
	queue<int> q;
	q.push(v);
	vector<bool> visited(g->numOfVertices);
	fill(visited.begin(), visited.end(), false);
	visited[v] = true;
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		// find edges with this vertex
		for (int i = 0; i < g->edges.size(); i++) {
			if (g->edges[i].v1 == s && visited[g->edges[i].v2] != true) {
				int v2 = g->edges[i].v2;
				g->distanceMatrix[v][v2] = g->distanceMatrix[v][s] + 1;
				if(g->distanceMatrix[v][v2] == 1) {
					g->adjacencyMatrix[v][v2] = 1;
					g->adjacencyMatrix[v2][v] = 1;
				}
				q.push(v2);
				visited[v2] = true;
				//cout << "Distance between " << v << " and " << v2 << " is " << g->distanceMatrix[v][v2] << endl;
			}
			else if (g->edges[i].v2 == s && visited[g->edges[i].v1] != true) {
				int v2 = g->edges[i].v1;
				g->distanceMatrix[v][v2] = g->distanceMatrix[v][s] + 1;
				q.push(v2);
				visited[v2] = true;
				//cout << "Distance between " << v << " and " << v2 << " is " << g->distanceMatrix[v][v2] << endl;
			}
		}
	}
}

// v is the vertex we are calculating the distance to each point from
// since the matrix is intialized with all -1 it will remain -1 if it isn't connected
bool DistanceMatrix(Graph *g) {
	for (int i = 0; i < g->numOfVertices; i++) {
		BFS(g, i);
	}
	for (int i = 0; i < g->numOfVertices; i++) {
		if (g->distanceMatrix[0][i] == -1)
			return false;
	}
	return true;
}

void printDistanceMatrix(Graph *g) {
	for (int i = 0; i < g->numOfVertices; i++) {
		for (int j = 0; j < g->numOfVertices; j++) {
			cout << setw(3) << g->distanceMatrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void printAdjacencyMatrix(Graph *g) {
	for (int i = 0; i < g->numOfVertices; i++) {
		for (int j = 0; j < g->numOfVertices; j++) {
			cout << setw(3) << g->adjacencyMatrix[i][j] << "  ";
		}
		cout << endl;
	}
}

int Diameter(Graph *g) {
	if (DistanceMatrix(g) == false)
		return -1;
	int max = 0;
	for (int i = 0; i < g->numOfVertices; i++) {
		for (int j = 0; j < g->numOfVertices; j++) {
			if (g->distanceMatrix[i][j] > max)
				max = g->distanceMatrix[i][j];
		}
	}
	return max;
}

vector< vector <int> > Components(Graph *g) {
	DistanceMatrix(g);
	vector<bool> verticesUsed;
	verticesUsed.resize(g->numOfVertices);
	fill(verticesUsed.begin(), verticesUsed.end(), false);
	vector< vector<int> > components;
	// Loops through rows of distance matrix
	for (int i = 0; i < g->numOfVertices; i++) {
		vector<int> connectedVertices;
		
		if (verticesUsed[i] == false) {
			
			// Loops through elements in the row
			for (int j = 0; j < g->numOfVertices; j++) {
				// Checks if the vertex of row i is connected to the vertex of row j
				if (g->distanceMatrix[i][j] != -1) {
					verticesUsed[j] = true;
					connectedVertices.push_back(j);
				}
			}
			components.push_back(connectedVertices);
		}
	}
	return components;
}

int main() {
	
	Graph *g = new Graph(4);
	g->edges.push_back(Edge(0, 1));
	g->edges.push_back(Edge(0, 2));
	g->edges.push_back(Edge(0, 3));
	g->edges.push_back(Edge(2, 3));
	g->edges.push_back(Edge(1, 3));
	/*Graph *g = new Graph(6);
	g->edges.push_back(Edge(0, 3));
	g->edges.push_back(Edge(4, 2));
	g->edges.push_back(Edge(2, 1));
	g->edges.push_back(Edge(5, 1));*/
	
	/*cout << g->numOfVertices << " vertices" << endl;
	for (int i = 0; i < g->edges.size(); i++) {
		cout << g->edges[i].v1 << " to " << g->edges[i].v2 << endl;
	}
	
	cout << "\n";*/
	bool connected = DistanceMatrix(g);
	
	cout << "Adjacency Matrix:" << endl;
	printAdjacencyMatrix(g);
	
	cout << "\nDistance Matrix:" << endl;
	printDistanceMatrix(g);
	
	if (connected == true) {
		cout << "\nDiameter: " << Diameter(g) << endl;
	}
	
	cout << "\nConnected Components:" << endl;
	
	vector< vector<int> > answer = Components(g);
	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			cout << setw(3) << answer[i][j] << "  ";
		}
		cout << endl;
	}
}




