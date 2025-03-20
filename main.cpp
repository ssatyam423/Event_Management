#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <iomanip>
#include<bits/stdc++.h>
using namespace std;

class Event {
public:
    int eventNumber;
    string name;
    tm date;
    string location;
    int guestCount;

    Event(int number, const string& name, const string& dateStr, const string& location, int guestCount) 
        : eventNumber(number), name(name), location(location), guestCount(guestCount) {
        istringstream ss(dateStr);
        ss >> get_time(&date, "%Y-%m-%d");
    }

    string getDateString() const {
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
        return string(buffer);
    }

    void print() const {
        cout << "🎉------------------------------------🎉" << endl;
        cout << "📌 Event #" << eventNumber << ": " << name << endl;
        cout << "📅 Date: " << getDateString() << endl;
        cout << "📍 Location: " << location << endl;
        cout << "👥 Guest Count: " << guestCount << endl;
        cout << "🎉------------------------------------🎉" << endl;
    }
};

class EventManager {
private:
    vector<Event> events;
    int eventCounter = 1;

public:
    void addEvent(const string& name, const string& date, const string& location, int guestCount) {
        events.emplace_back(eventCounter++, name, date, location, guestCount);
        cout << "✅ Event added successfully!" << endl;
    }

    void removeEvent(const string& name) {
        auto it = remove_if(events.begin(), events.end(), 
                                [&](const Event& event) { return event.name == name; });
        if (it != events.end()) {
            events.erase(it, events.end());
            cout << "🗑️ Event '" << name << "' removed successfully!" << endl;
        } else {
            cout << "❌ Event not found." << endl;
        }
    }

    void editEvent(const string& name, const string& newName, const string& newDate, const string& newLocation, int newGuestCount) {
        for (auto& event : events) {
            if (event.name == name) {
                event.name = newName;
                istringstream ss(newDate);
                ss >> get_time(&event.date, "%Y-%m-%d");
                event.location = newLocation;
                event.guestCount = newGuestCount;
                cout << "✏️ Event updated successfully!" << endl;
                return;
            }
        }
        cout << "❌ Event not found." << endl;
    }

    void searchEventByName(const string& name) const {
        for (const auto& event : events) {
            if (event.name == name) {
                event.print();
                return;
            }
        }
        cout << "❌ Event not found." << endl;
    }

    void filterEventsByLocation(const string& location) const {
        bool found = false;
        for (const auto& event : events) {
            if (event.location == location) {
                event.print();
                found = true;
            }
        }
        if (!found) cout << "❌ No events found at " << location << endl;
    }

    void listEvents() const {
        if (events.empty()) {
            cout << "❌ No events scheduled." << endl;
            return;
        }

        vector<Event> sortedEvents = events;
        sort(sortedEvents.begin(), sortedEvents.end(), [](const Event& a, const Event& b) {
            return mktime(const_cast<tm*>(&a.date)) < mktime(const_cast<tm*>(&b.date));
        });

        for (const auto& event : sortedEvents) {
            event.print();
        }
    }
};

int main() {
    EventManager manager;
    int choice;
    do {
        cout << "\n✨====================================✨" << endl;
        cout << "  🎊 Event Management System 🎊  " << endl;
        cout << "✨====================================✨" << endl;
        cout << "1️⃣  Add Event" << endl;
        cout << "2️⃣  Remove Event" << endl;
        cout << "3️⃣  Edit Event" << endl;
        cout << "4️⃣  Search Event" << endl;
        cout << "5️⃣  Filter Events by Location" << endl;
        cout << "6️⃣  List Events" << endl;
        cout << "7️⃣  Exit" << endl;
        cout << "✨====================================✨" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        string name, date, location, newName;
        int guestCount;

        switch (choice) {
            case 1:
                cout << "Enter name, date (YYYY-MM-DD), location, guest count: ";
                getline(cin, name);
                getline(cin, date);
                getline(cin, location);
                cin >> guestCount;
                cin.ignore();
                manager.addEvent(name, date, location, guestCount);
                break;
            case 2:
                cout << "Enter event name to remove: ";
                getline(cin, name);
                manager.removeEvent(name);
                break;
            case 3:
                cout << "Enter event name to edit: ";
                getline(cin, name);
                cout << "Enter new name, new date (YYYY-MM-DD), new location, new guest count: ";
                getline(cin, newName);
                getline(cin, date);
                getline(cin, location);
                cin >> guestCount;
                cin.ignore();
                manager.editEvent(name, newName, date, location, guestCount);
                break;
            case 4:
                cout << "Enter event name to search: ";
                getline(cin, name);
                manager.searchEventByName(name);
                break;
            case 5:
                cout << "Enter location to filter events: ";
                getline(cin, location);
                manager.filterEventsByLocation(location);
                break;
            case 6:
                manager.listEvents();
                break;
            case 7:
                cout << "🚪 Exiting..." << endl;
                break;
            default:
                cout << "❌ Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
    return 0;
}


