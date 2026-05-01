#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Structure to represent a single game move
struct Move {
    int playerID;
    string action;
    string position;

    void display() const {
        cout << "[Player " << playerID << ": " << action << " at " << position << "]";
    }
};

class GameMoveTracker {
private:
    stack<Move> undoStack;
    stack<Move> redoStack;

public:
    // Records a new move and clears the redo history
    void recordMove(int id, const string& act, const string& pos) {
        Move newMove = {id, act, pos};
        undoStack.push(newMove);

        // Clear redo history when a new move is made
        while (!redoStack.empty()) {
            redoStack.pop();
        }

        cout << "Recorded: ";
        newMove.display();
        cout << endl;
    }

    // Undo last move
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        Move lastMove = undoStack.top();
        undoStack.pop();
        redoStack.push(lastMove);

        cout << "Undid: ";
        lastMove.display();
        cout << endl;
    }

    // Redo last undone move
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        Move recoveredMove = redoStack.top();
        redoStack.pop();
        undoStack.push(recoveredMove);

        cout << "Redid: ";
        recoveredMove.display();
        cout << endl;
    }

    // Show current game status
    void showStatus() const {
        cout << "\n--- Current Game State ---" << endl;
        if (undoStack.empty()) {
            cout << "Board is empty." << endl;
        } else {
            cout << "Last move: ";
            undoStack.top().display();
            cout << "\nTotal moves in history: " << undoStack.size() << endl;
        }
        cout << "--------------------------\n" << endl;
    }
};

int main() {
    GameMoveTracker tracker;
    int choice;

    cout << "--- Stack-Based Move Tracker ---" << endl;

    while (true) {
        cout << "1. Record Move  2. Undo  3. Redo  4. Show Status  5. Exit\n";
        cout << "Selection: ";
        
        if (!(cin >> choice)) { // Handle invalid input gracefully
            cout << "Invalid input. Exiting..." << endl;
            break;
        }

        if (choice == 1) {
            int id;
            string act, pos;
            cout << "Enter Player ID, Action (e.g., Place), and Position (e.g., A1): ";
            cin >> id >> act >> pos;
            tracker.recordMove(id, act, pos);
        } 
        else if (choice == 2) {
            tracker.undo();
        } 
        else if (choice == 3) {
            tracker.redo();
        } 
        else if (choice == 4) {
            tracker.showStatus();
        } 
        else if (choice == 5) {
            cout << "Exiting program..." << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}