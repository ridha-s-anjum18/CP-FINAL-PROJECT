#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

struct Player {
    string name;
    string playerClass;
    int health;
    int experience;
};

struct Quest {
    string name;
    int difficultyLevel;
};

struct Enemy {
    string name;
    int difficultyLevel;
};

void createCharacter(Player& player) {
    cout << "Enter your character's name: ";
    cin >> player.name;
    cout << "Choose a class (Warrior, Mage, Rogue): ";
    cin >> player.playerClass;
    player.health = 100;
    player.experience = 0;
}

void displayCharacterInfo(const Player& player) {
    cout << "Player: " << player.name << " (" << player.playerClass << ")\n";
    cout << "Health: " << player.health << "\n";
    cout << "Experience: " << player.experience << "\n";
}

void battle(Player& player, const Enemy& enemy) {
    cout << "You encounter a " << enemy.name << ". Prepare for battle!\n";

    int consecutiveVictories = 0;

    for (int round = 1; round <= 3; ++round) {
        cout << "Round " << round << ": ";
        int playerAttack;
        cout << "Enter your attack : ";
        cin >> playerAttack;

        int enemyAttack = rand() % 100 + enemy.difficultyLevel;
        cout << "Enemy Attack: " << enemyAttack << ".\n";

        if (playerAttack > enemyAttack) {
            cout << "Victory! You dealt a powerful blow to the " << enemy.name << ".\n";
            player.experience += 10;
            consecutiveVictories++;
        }
        else {
            cout << "Defeat! The " << enemy.name << " countered your attack.\n";
            player.health -= 10;
            consecutiveVictories = 0;
        }

        cout << "Player Health: " << player.health << " | Experience: " << player.experience << "\n";

        if (player.health <= 0) {
            cout << "Game Over! Your character has run out of health.\n";
            return;
        }

        if (player.experience >= 50) {
            player.health += 20;
            player.experience = 0;
            consecutiveVictories = 0;
            cout << "Congratulations! You leveled up!\n";
        }

        if (player.health > 0 && consecutiveVictories >= 3) {
            player.health += 20;
            player.experience = 0;
            cout << "Congratulations! You defeated three rounds in a row and leveled up!\n";
            consecutiveVictories = 0;
        }
    }
}

void handleQuest(Player& player, const Quest& quest) {
    cout << "Embarking on quest: " << quest.name << " (Difficulty Level: " << quest.difficultyLevel << ")\n";

    vector<Enemy> enemies;
    for (int i = 0; i < 3; ++i) {
        enemies.push_back({ "Enemy " + to_string(i + 1), quest.difficultyLevel });
    }

    for (const Enemy& enemy : enemies) {
        battle(player, enemy);

        if (player.health <= 0) {
            cout << "Game Over! Your character has run out of health.\n";
            return;
        }
    }
}

void embarkOnQuest(Player& player, const vector<Quest>& quests) {
    cout << "Available Quests:\n";
    for (size_t i = 0; i < quests.size(); ++i) {
        cout << i + 1 << ". " << quests[i].name << " (Difficulty Level: " << quests[i].difficultyLevel << ")\n";
    }

    cout << "Choose a quest by entering the corresponding number: ";
    int questChoice;
    cin >> questChoice;

    if (questChoice > 0 && static_cast<size_t>(questChoice) <= quests.size()) {
        Quest selectedQuest = quests[questChoice - 1];
        handleQuest(player, selectedQuest);
    }
    else {
        cout << "Invalid quest choice.\n";
    }
}

void gameLoop(Player& player, const vector<Quest>& quests) {
    while (true) {
        displayCharacterInfo(player);
        embarkOnQuest(player, quests);

        cout << "Do you want to continue? (yes/no): ";
        string userChoice;
        cin >> userChoice;
        if (userChoice != "yes") {
            break;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Player player;
    vector<Quest> quests = { {"Quest 1", 1}, {"Quest 2", 2}, {"Quest 3", 3} };

    createCharacter(player);
    gameLoop(player, quests);

    return 0;
}