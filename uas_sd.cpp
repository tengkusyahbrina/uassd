#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <stack>


using namespace std;

struct Produk {
    int id;
    string nama;
    string kategori;
    int harga;
};

struct Node {
    Produk data;
    Node* next;
};


unordered_map<int, Produk> produkMap;
stack<Node*> undoStack; 
extern Node* head; 

string formatRupiah(double harga) {
    stringstream ss;
    ss << "Rp " << fixed << setprecision(0) << harga;
    return ss.str();
}

void printLine(char ch = '=', int length = 50) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    cout << endl;
}

void printHeader() {
    printLine('*', 50);
    cout << "*        SELAMAT DATANG DI TOKO (GO GURL)        *" << endl;
    printLine('*', 50);
    cout << endl;
}

void displayMenu() {
    printLine('-', 50);
    cout << "                  MASUK KE MENU" << endl;
    printLine('-', 50);
    cout << "| 1 | Pilih kategori belanja                  |" << endl;
    cout << "| 2 | Kelola List                             |" << endl;
    cout << "| 3 | Pembayaran                              |" << endl;
    cout << "| 0 | Exit                                    |" << endl;
    printLine('-', 50);
}

string getCurrentTime() {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S pada %d/%m/%Y", localTime);
    return string(buffer);
}

string getFilename(const string& nama) {
    time_t now = time(0);
    tm *localTime = localtime(&now);
    char buffer[50];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localTime);
    return nama + "_" + buffer + ".txt";
}

void saveReceipt(const string& nama, double totalAmount, double amountPaid, double change) {
    string filename = getFilename(nama);
    ofstream file(filename);
    if (file.is_open()) {
        file << "===========================\n";
        file << "       STRUK PEMBAYARAN\n";
        file << "===========================\n";
        file << "Nama Pelanggan: " << nama << endl;
        file << "Jumlah Pembayaran: Rp" << fixed << setprecision(2) << totalAmount << endl;
        file << "Jumlah Dibayar: Rp" << fixed << setprecision(2) << amountPaid << endl;
        file << "Kembalian: Rp" << fixed << setprecision(2) << change << endl;
        file << "Waktu Pembayaran: " << getCurrentTime() << endl;
        file << "===========================\n";
        file << "   Terima kasih telah\n";
        file << "   berbelanja di Toko (GO GURL)!\n";
        file << "===========================\n";
        file.close();
        cout << "Struk pembayaran berhasil disimpan sebagai '" << filename << "'\n";
    } else {
        cout << "Gagal menyimpan struk pembayaran.\n";
    }
}

void paymentMenu(const string& nama) {
    double totalAmount = 0.0;
    Node* temp = head;

    while (temp != nullptr) {
        totalAmount += temp->data.harga;
        temp = temp->next;
    }

    cout << "=== Menu Pembayaran ===\n";
    cout << "Pembayaran atas nama: " << nama << endl;
    cout << "Total Pembayaran: Rp" << fixed << setprecision(2) << totalAmount << endl;

    double amountPaid;
    cout << "Masukkan jumlah pembayaran: ";
    cin >> amountPaid;

    if (amountPaid < totalAmount) {
        cout << "Uang yang dibayarkan kurang dari total pembayaran!\n";
    } else {
        double change = amountPaid - totalAmount;
        cout << "\nPembayaran untuk " << nama << " sebesar Rp" << fixed << setprecision(2) << totalAmount
             << " berhasil.\n";
        cout << "Jumlah yang dibayarkan: Rp" << fixed << setprecision(2) << amountPaid << endl;
        cout << "Kembalian: Rp" << fixed << setprecision(2) << change << endl;
        cout << "Waktu Pembayaran: " << getCurrentTime() << endl;

        saveReceipt(nama, totalAmount, amountPaid, change);
    }
}


void printFarewell(const string& nama) {
    int totalWidth = 50;
    int nameLength = nama.length();
    int padding = totalWidth - 2 - 14 - nameLength;
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;

    printLine('*', totalWidth);
    cout << "*" << string(leftPadding, ' ') << "SAMPAI JUMPA, " << nama << string(rightPadding, ' ') << "*" << endl;
    printLine('*', totalWidth);
}

vector<Produk> daftarProduk = {
    {1, "Beras", "Konsumsi", 50000}, {2, "Mi Instan", "Konsumsi", 3000},
    {3, "Minyak Goreng", "Konsumsi", 20000}, {4, "Telur", "Konsumsi", 25000},
    {5, "Gula", "Konsumsi", 15000}, {6, "Kopi", "Konsumsi", 10000},
    {7, "Teh", "Konsumsi", 8000}, {8, "Roti", "Konsumsi", 12000},
    {9, "Cokelat", "Konsumsi", 18000}, {10, "Susu", "Konsumsi", 22000},
    {11, "Buah Apel", "Konsumsi", 30000}, {12, "Jeruk", "Konsumsi", 28000},
    {13, "Daging Sapi", "Konsumsi", 120000}, {14, "Ikan", "Konsumsi", 45000},
    {15, "Sayur Bayam", "Konsumsi", 5000}, {16, "Smartphone", "Elektronik", 2500000},
    {17, "Laptop", "Elektronik", 7500000}, {18, "Tablet", "Elektronik", 3200000},
    {19, "Televisi", "Elektronik", 4000000}, {20, "Kipas Angin", "Elektronik", 250000},
    {21, "AC", "Elektronik", 3000000}, {22, "Kulkas", "Elektronik", 2800000},
    {23, "Mesin Cuci", "Elektronik", 2500000}, {24, "Setrika", "Elektronik", 300000},
    {25, "Speaker", "Elektronik", 1000000}, {26, "Headphone", "Elektronik", 800000},
    {27, "Mouse", "Elektronik", 150000}, {28, "Keyboard", "Elektronik", 350000},
    {29, "Power Bank", "Elektronik", 500000}, {30, "Charger", "Elektronik", 200000},
    {31, "Lipstik", "Kecantikan", 100000}, {32, "Bedak", "Kecantikan", 85000},
    {33, "Maskara", "Kecantikan", 120000}, {34, "Foundation", "Kecantikan", 150000},
    {35, "Parfum", "Kecantikan", 300000}, {36, "Pelembap", "Kecantikan", 90000},
    {37, "Serum Wajah", "Kecantikan", 200000}, {38, "Sabun Muka", "Kecantikan", 75000},
    {39, "Shampoo", "Kecantikan", 50000}, {40, "Conditioner", "Kecantikan", 55000},
    {41, "Lulur", "Kecantikan", 40000}, {42, "Masker Rambut", "Kecantikan", 60000},
    {43, "Cat Kuku", "Kecantikan", 25000}, {44, "Sunblock", "Kecantikan", 70000},
    {45, "Toner", "Kecantikan", 80000}, {46, "Sepatu Lari", "Olahraga", 500000},
    {47, "Bola Sepak", "Olahraga", 250000}, {48, "Raket Badminton", "Olahraga", 300000},
    {49, "Pakaian Olahraga", "Olahraga", 150000}, {50, "Topi", "Olahraga", 50000},
    {51, "Jersey", "Olahraga", 120000}, {52, "Matras Yoga", "Olahraga", 200000},
    {53, "Kettlebell", "Olahraga", 400000}, {54, "Treadmill", "Olahraga", 5000000},
    {55, "Sepeda", "Olahraga", 2000000}, {56, "Dumbbell", "Olahraga", 350000},
    {57, "Skipping Rope", "Olahraga", 100000}, {58, "Pelindung Lutut", "Olahraga", 75000},
    {59, "Sarung Tangan Gym", "Olahraga", 80000}, {60, "Botol Minum", "Olahraga", 30000},
    {61, "Boneka", "Mainan", 50000}, {62, "Mobil-mobilan", "Mainan", 40000},
    {63, "Lego", "Mainan", 500000}, {64, "Puzzle", "Mainan", 150000},
    {65, "Drone", "Mainan", 1200000}, {66, "Robot", "Mainan", 800000},
    {67, "Mainan Kayu", "Mainan", 100000}, {68, "Kereta Api Mini", "Mainan", 250000},
    {69, "Sepeda Anak", "Mainan", 700000}, {70, "Alat Musik Anak", "Mainan", 300000},
    {71, "Balok Bangunan", "Mainan", 200000}, {72, "Mainan Edukasi", "Mainan", 150000},
    {73, "Game Konsol", "Mainan", 3500000}, {74, "Mainan Air", "Mainan", 60000},
    {75, "Mainan Pasir", "Mainan", 50000}
};

vector<Produk> keranjangBelanja;

void displayCategoryMenu() {
    printLine('-', 50);
    cout << "             PILIH KATEGORI BELANJA" << endl;
    printLine('-', 50);
    cout << "| 1 | Konsumsi                              |" << endl;
    cout << "| 2 | Elektronik                            |" << endl;
    cout << "| 3 | Kecantikan                            |" << endl;
    cout << "| 4 | Olahraga                              |" << endl;
    cout << "| 5 | Mainan                                |" << endl;
    cout << "| 0 | Kembali ke menu utama                 |" << endl;
    printLine('-', 50);
}
Node* head = nullptr;

void addToCart(int itemIndex) {
    Produk produk = daftarProduk[itemIndex - 1];
    Node* newNode = new Node{produk, nullptr};

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "-> " << produk.nama << " telah ditambahkan ke keranjang belanja.\n";
}

void tampilkanListBelanja() {
    if (head == nullptr) {
        cout << "\nList belanja kosong.\n";
        return;
    }

    cout << "\nList belanja Anda:\n";
    Node* temp = head;
    int index = 1;

    while (temp != nullptr) {
        cout << index << ". " << temp->data.nama << " - " << formatRupiah(temp->data.harga) << "\n";
        temp = temp->next;
        index++;
    }
}


void displayItems(const string& category) {
    cout << "List barang " << category << ":" << endl;
    for (const auto& produk : daftarProduk) {
        if (produk.kategori == category) {
            cout << produk.id << ". " << produk.nama << " - Rp" << produk.harga << endl;
        }
    }
    cout << "0. Kembali ke menu kategori" << endl;
}

void categoryMenu() {
    int categoryChoice;
    do {
        displayCategoryMenu();
        cout << "Pilih kategori [0-5]: ";
        cin >> categoryChoice;

        if (categoryChoice == 0) {
            break;
        }

        string category;
        switch (categoryChoice) {
            case 1: category = "Konsumsi"; break;
            case 2: category = "Elektronik"; break;
            case 3: category = "Kecantikan"; break;
            case 4: category = "Olahraga"; break;
            case 5: category = "Mainan"; break;
            default:
                cout << "-> Pilihan tidak valid. Silakan coba lagi!" << endl;
                continue;
        }

        int itemChoice;
        char addMore;
        do {
            displayItems(category);
            cout << "Pilih barang [0-" << daftarProduk.size() << "]: ";
            cin >> itemChoice;

            if (itemChoice > 0 && itemChoice <= daftarProduk.size() && daftarProduk[itemChoice - 1].kategori == category) {
                cout << "-> Anda memilih: " << daftarProduk[itemChoice - 1].nama << endl;
                cout << "Menambahkan Produk Tersebut (y/t)?: ";
                cin >> addMore;

                if (addMore == 't' || addMore == 'T') {
                    tampilkanListBelanja(); 
                    cout << "Kembali ke menu kategori..." << endl;
                    break;
                } else {
                    addToCart(itemChoice); 
                }
            } else if (itemChoice == 0) {
                cout << "Kembali ke menu kategori..." << endl;
            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi!" << endl;
            }
        } while (itemChoice != 0);

    } while (true);
}



void tambahKeList(Produk produk) {
    Node* nodeBaru = new Node{produk, nullptr};
    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
}


void tukarPosisi(int posisi1, int posisi2) {
    if (posisi1 == posisi2) return;

    Node *prev1 = nullptr, *curr1 = head;
    Node *prev2 = nullptr, *curr2 = head;

    int count = 1;

    while (curr1 != nullptr && count < posisi1) {
        prev1 = curr1;
        curr1 = curr1->next;
        count++;
    }

    count = 1;
    while (curr2 != nullptr && count < posisi2) {
        prev2 = curr2;
        curr2 = curr2->next;
        count++;
    }

    if (curr1 == nullptr || curr2 == nullptr) return;

    if (prev1 != nullptr) prev1->next = curr2;
    else head = curr2;

    if (prev2 != nullptr) prev2->next = curr1;
    else head = curr1;

    Node* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
}

void hapusPosisi(int posisi) {
    if (head == nullptr) return;

    Node *temp = head, *prev = nullptr;
    int count = 1;

    while (temp != nullptr && count < posisi) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (temp == nullptr) return;

    if (prev != nullptr) prev->next = temp->next;
    else head = temp->next;

    undoStack.push(temp);
    cout << "\nItem \"" << temp->data.nama << "\" dihapus dari list belanja.\n";
}

void undoHapus() {
    if (undoStack.empty()) {
        cout << "\nTidak ada perintah untuk di-undo.\n";
        return;
    }

    Node* node = undoStack.top();
    undoStack.pop();

    node->next = head;
    head = node;

    cout << "\nUndo berhasil. Item \"" << node->data.nama << "\" dikembalikan ke list belanja.\n";
}

void kelolaListBelanja() {
    int pilihan;
    do {
        cout << "\n=== KELOLA LIST BELANJA ===\n";
        cout << "1. Tampilkan List Belanja\n";
        cout << "2. Tukar Posisi List\n";
        cout << "3. Hapus Item\n";
        cout << "4. Undo Hapus\n";
        cout << "5. Kembali ke Menu Utama\n";
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tampilkanListBelanja();
            break;
        case 2: {
            int pos1, pos2;
            cout << "\nMasukkan posisi pertama: ";
            cin >> pos1;
            cout << "Masukkan posisi kedua: ";
            cin >> pos2;
            tukarPosisi(pos1, pos2);
            cout << "\nPosisi berhasil ditukar.\n";
            break;
        }
        case 3: {
            int posisi;
            cout << "\nMasukkan posisi item yang ingin dihapus: ";
            cin >> posisi;
            hapusPosisi(posisi);
            break;
        }
        case 4:
            undoHapus();
            break;
        case 5:
            cout << "\nKembali ke menu utama...\n";
            break;
        default:
            cout << "\nPilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

int main() {
    string nama;
    int pilihan;

    printHeader();
    cout << "Masukkan nama Anda: ";
    getline(cin, nama);
    cout << endl;
    cout << "Halo, " << nama << "! Selamat berbelanja di Toko (GO GURL)!" << endl;

    do {
        displayMenu();
        cout << "Pilih menu [0-3]: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                categoryMenu();
                break;
            case 2:        
               kelolaListBelanja();
                break;
            case 3:
                paymentMenu(nama);
                break;
            case 0:
                cout << "-> Terima kasih telah berbelanja di Toko (GO GURL), " << nama << "!" << endl;
                break;
            default:
                cout << "-> Pilihan tidak valid. Silakan coba lagi!" << endl;
        }
    } while (pilihan != 0);

    printFarewell(nama);

    return 0;
}