#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class User {
public:
    string username;
    string password;

    User(string username, string password) : username(username), password(password) {}

    bool authenticate(string inputUsername, string inputPassword) {
        return (username == inputUsername && password == inputPassword);
    }

    void updatePassword(string newPassword) {
        password = newPassword;
    }
};

class Question {
public:
    string text;
    vector<string> options;
    int correctOption;

    Question(string text, vector<string> options, int correctOption)
        : text(text), options(options), correctOption(correctOption) {}
};

class Exam {
public:
    vector<Question> questions;
    int currentQuestionIndex;
    time_t startTime;
    time_t endTime;

public:
    Exam(vector<Question> questions, int duration)
        : questions(questions), currentQuestionIndex(0) {
        startTime = time(nullptr);
        endTime = startTime + duration;
    }

    bool hasTimeLeft() {
        time_t currentTime = time(nullptr);
        return currentTime < endTime;
    }

    Question getCurrentQuestion() {
        return questions[currentQuestionIndex];
    }

    void moveToNextQuestion() {
        if (currentQuestionIndex < questions.size() - 1) {
            currentQuestionIndex++;
        }
    }
};


int main() {
    User user("Priti", "12345");
    vector<Question> questions;

    vector<string> question1Options;
    question1Options.push_back("Droupadi Murmu");
    question1Options.push_back("Ram Nath Kovind");
    question1Options.push_back("Naveen Patnaik");
    question1Options.push_back("Pratibha Patil");
    questions.push_back(Question("Who is the president of India?", question1Options, 1));

    vector<string> question2Options;
    question2Options.push_back("Douglas Engelbart");
    question2Options.push_back("Charles Babbage");
    question2Options.push_back("René Sommer");
    question2Options.push_back("Christopher Sholes");
    questions.push_back(Question("Who invented Computer?", question2Options, 2));


    Exam exam(questions, 300); 

    string inputUsername, inputPassword;
    cout << "Login\n";
    cout << "Username: ";
    cin >> inputUsername;
    cout << "Password: ";
    cin >> inputPassword;

    if (user.authenticate(inputUsername, inputPassword)) {
        cout << "Login successful!\n";

        while (exam.hasTimeLeft()) {
            Question currentQuestion = exam.getCurrentQuestion();
            cout << "Displaying question: " << currentQuestion.text << endl;

            for (int i = 0; i < currentQuestion.options.size(); ++i) {
                cout << i + 1 << ". " << currentQuestion.options[i] << endl;
            }

            int selectedOption;
            cout << "Select an option: ";
            cin >> selectedOption;

            // Clear the input buffer
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (selectedOption == currentQuestion.correctOption) {
                cout << "CORRECT ANSWER!\n";
            } else {
                cout << "INCORRECT ANSWER!\n";
            }

            if (exam.currentQuestionIndex < questions.size() - 1) {
                exam.moveToNextQuestion();
            }
        }
    } else {
        cout << "Login failed. Exiting...\n";
    }

    return 0;
}
