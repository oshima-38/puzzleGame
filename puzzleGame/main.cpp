#include<iostream>

using namespace std;

char inputKey;

int wallPosition[22] = {0,1,2,3,4,5,6,7,8,15,16,23,24,31,32,33,34,35,36,37,38,39};

int playerPosition = 14;

int goal1Position = 9;
int goal2Position = 10;

int nimotsu1Position = 17;
int nimotsu2Position = 18;

bool clearFlg = false;

enum KEY {
	UP = 'w',
	DOWN = 'z',
	LEFT = 'a',
	RIGHT ='s'
};

bool isWall(int position) {
	auto itr = find(begin(wallPosition), end(wallPosition), position);

	// 移動後の位置が壁であるか
	if (itr != end(wallPosition)) {
		return true;
	}
	else {
		return false;
	}

}

bool isPlayer(int position) {
	if (playerPosition == position) {
		return true;
	}
	else {
		return false;
	}
}

bool isGoal(int position) {
	if (goal1Position == position || goal2Position == position) {
		return true;
	}
	else {
		return false;
	}
}

bool isNimotsu(int position) {
	if (nimotsu1Position == position || nimotsu2Position == position) {
		return true;
	}
	else {
		return false;
	}
}

int moveNimotsu(int nimotsuPosition) {
	int _nimotsuPosition = nimotsuPosition;
	// 下から来た
	if (inputKey == UP && nimotsuPosition == playerPosition - 8) {
		_nimotsuPosition -= 8;
	}
	// 上から来た
	else if (inputKey == DOWN && nimotsuPosition == playerPosition + 8) {
		_nimotsuPosition += 8;
	}
	// 右から来た
	else if (inputKey == LEFT && nimotsuPosition == playerPosition - 1) {
		_nimotsuPosition -= 1;
	}
	// 左から来た
	else if (inputKey == RIGHT && nimotsuPosition == playerPosition + 1) {
		_nimotsuPosition += 1;
	}

	if (!isWall(_nimotsuPosition) && !isNimotsu(_nimotsuPosition)) {
		return _nimotsuPosition;
	}

	return nimotsuPosition;
}

void movePlayer() {
	int _playerPosition = playerPosition;
	// キー入力判定
	if (inputKey == UP) {
		_playerPosition -= 8;
	}
	else if (inputKey == DOWN) {
		_playerPosition += 8;
	}
	else if (inputKey == LEFT) {
		_playerPosition -= 1;
	}
	else if (inputKey == RIGHT) {
		_playerPosition += 1;
	}

	if (!isWall(_playerPosition) && !isNimotsu(_playerPosition)) {
		playerPosition = _playerPosition;
	}
}

void getInput() {
	cin >> inputKey;
}

void updateGame() {
	// 荷物1の移動
	nimotsu1Position = moveNimotsu(nimotsu1Position);
	// 荷物2の移動
	nimotsu2Position = moveNimotsu(nimotsu2Position);
	// プレイヤーの移動
	movePlayer();
}

void draw() {
	string output = "";
	for (int i = 0; i < 40; i++) {
		if (isWall(i)) {
			output += "#";
		}
		else if (isNimotsu(i)) {
			if (isGoal(i)) {
				output += "O";
			}
			else {
				output += "o";
			}
		}
		else if (isGoal(i)) {
			if (isPlayer(i)) {
				output += "P";
			}
			else {
				output += ".";

			}
		}
		else if (isPlayer(i)) {
				output += "p";
		}
		else {
			output += " ";
		}

		if (i % 8 == 7) {
			cout << output << endl;
			output = "";
		}
	}
}

void clearCheck() {
	if (goal1Position == nimotsu1Position || goal1Position == nimotsu2Position) {
		if (goal2Position == nimotsu1Position || goal2Position == nimotsu2Position) {
			clearFlg = true;
		}
	}
}

int main() {

	draw();
	while (true) {
		getInput();
		updateGame();
		draw();
		clearCheck();
		if (clearFlg) {
			cout << "Congratulation's! you won." << endl;
			break;
		}
	}

	return 0;
}