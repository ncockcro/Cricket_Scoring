/*
Written by: Nicholas Cockcroft
Date: June 6, 2018

Description: This is a program to simulate reading in a typical score from a "Cricket" game.
The user will type in the scores of a match and this program will output the scores of the
players who played. A typical score of Cricket could look like:

1.2wW6.2b34

 - (number) means the number of runs to a player on strike
 - '.' means no runs
 - 'b' means "a bye" which is 1 run to a team but not a particular player
 - 'w' means "a wide" which is 1 run to a team but not a particular player
 - 'W' means a batsman is out and a new player takes over

For more information please refer to:
https://www.reddit.com/r/dailyprogrammer/comments/7x81yg/20180213_challenge_351_easy_cricket_scoring/
*/

#include <iostream>
#include <string>
using namespace std;

int CheckScore(char point);

void SwitchPlayers(int &player1, int &player2);

void NewPlayer(int &player1, int &player2);

int main() {

	// Initial Variables
	string cricketScore;
	int score = 0;

	// Get the score of the game from the user
	cout << "Enter the score of the Cricket game: ";
	cin >> cricketScore;

	// All variables used for parsing the score that was entered in
	const int PLAYERS = 22; // The most amount of players that can be in a Cricket game are 22
	int playerScores[PLAYERS] = { 0 };
	int extraScore = 0; // Keeps track of the "Extras" score
	int currentPlayer = 0; // Holds the player that is currently at bat
	int otherPlayer = 1; // Holds the other player that will play after the other player is "out"
	int switchBases = 0; // Keeps track of switching bases after 6 legal plays

	// Go through each character of the Cricket score
	for (size_t i = 0; i < cricketScore.length(); i++) {

		// Get the current score of the spefic spot were parsing
		score = CheckScore(cricketScore[i]);

		// -1 means it was a 'b'
		if (score == -1) {
			SwitchPlayers(currentPlayer, otherPlayer);
			extraScore++;
			switchBases++;
		}
		// -2 means it was a 'w'
		else if (score == -2) {
			extraScore++;
		}
		// -3 means it was a 'W'
		else if (score == -3) {
			NewPlayer(currentPlayer, otherPlayer);
			switchBases++;
		}
		// Anything else will either be 0 or a positive score
		else {
			// If the score is odd, then we need to switch players
			if ((score % 2) == 1) {
				playerScores[currentPlayer] += score;
				SwitchPlayers(currentPlayer, otherPlayer);
				switchBases++;
			}
			// Otherwise, the current player keeps playing
			else {
				playerScores[currentPlayer] += score;
				switchBases++;
			}
		}

		// Once there has been six "legal" turn, we switch players
		if (switchBases == 6) {
			switchBases = 0;
			SwitchPlayers(currentPlayer, otherPlayer);
		}

	}

	// Outputting results of the scores of the players
	for (int i = 0; i < PLAYERS; i++) {
		if (playerScores[i] != 0) {
			cout << "P" << i + 1 << " "<< playerScores[i] << endl;
		}
	}
	cout << "Extras: " << extraScore << endl;

	return 0;
}

// Checks the point that was passed in and determines which of the 5 types it falls under
int CheckScore(char point) {
	if (point == '.') {
		return 0;
	}
	else if (point == 'b') {
		return -1;
	}
	else if (point == 'w') {
		return -2;
	}
	else if (point == 'W') {
		return -3;
	}
	else if (point > 0) {
		return point - '0';
	}
	else {
		cout << "Error, unknown score. Exiting program.";
		system("pause");
		exit(1);

	}
}

// Switches the current player with the other player
void SwitchPlayers(int &player1, int &player2) {
	int temp;

	temp = player1;
	player1 = player2;
	player2 = temp;
}

// If a player strikes out, a new player will join the game
void NewPlayer(int &player1, int &player2) {
	if ((player1 + 1) == player2) {
		player1 += 2;
	}
	else {
		player1++;
	}
}