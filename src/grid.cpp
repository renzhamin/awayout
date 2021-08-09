#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const int M = 8;

vector<vector<int>> grid(N, vector<int>(M, -1));
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool valid(int x, int y) {
	if(x < 0 or x >= N or y < 0 or y >=M)
		return false;
	return true;
}

vector <vector<int>> generate() {
	
	vector<vector<int>> genGrid(N, vector<int>(M, -1));

	int x = rand() % N, y = rand() % M, cnt = 1;
	//cout << x << " " << y << "\n";
	genGrid[x][y] = 0;

	while(true) {
		int nx, ny;
		bool stuck = true;
		vector <int> ok;

		for(int i=0; i<4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if(valid(nx, ny) and genGrid[nx][ny] == -1) {
				stuck = false;
				ok.emplace_back(i);
			}
		}

		if(stuck)
			break;

		int pos = rand() % ok.size();
		x += dx[ok[pos]];
		y += dy[ok[pos]];
		//cout << x << " " << y << "\n";
		genGrid[x][y] = cnt++;
	}

	return genGrid;
}

void findGoodGrid()
{
	int prevBadness = 1e9+7, badness;

	for(int T=0; T < 100; ++T) {
		badness = 0;
		vector <vector<int>> tempGrid = generate();
		for(int i=0; i<N; ++i){
			for(int j=0; j<M;++j){
				if(tempGrid[i][j] == -1){
					int blockBadness = 1;
					for(int k=0; k<4; ++k) {
						if(valid(i+dx[k], j+dy[k]) and tempGrid[i+dx[k]][j+dy[k]] == -1)
							blockBadness *= 2;
					}
					badness += blockBadness;
				}
			}
		}
		if(badness < prevBadness){
			grid = tempGrid;
			prevBadness = badness;
		}
	}

	cout << "Final badness " << prevBadness << "\n";
}

void showGrid()
{
	srand(time(NULL));
	findGoodGrid();

	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) { 
			if(grid[i][j] != -1)
				cout << grid[i][j] << "\t";
			else
				cout << "#\t";
		}
		cout << "\n";
	}
}


// int main(){
//     showGrid();
// }