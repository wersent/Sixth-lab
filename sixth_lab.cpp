#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <random>
#include <vector>
using std::cin;
using std::swap;
using std::endl;


std::default_random_engine generator; // Объекты, генерирующие равномерно распределенные числа.
std::uniform_int_distribution<int> distribution(1,100); // Объекты, которые преобразуют последовательности чисел, сгенерированные генератором, в последовательности чисел, 
                                                        // которые соответствуют определенному распределению случайных величин.
int digitsSum(int n, bool highestNumber, bool same_numerals) {
  int sum{0}, max_num{0}, num{n % 10};
  while (n != 0) {
    sum += n % 10;
    max_num = std::max(max_num, n % 10);
    if (same_numerals && n % 10 != num) return false;
    n /= 10;
  }
  if (highestNumber) return max_num;
  return sum;
}
void task1(){
    bool go = true;
    int n[10000]{0};
    for (int i = 0; i < 10000; i++){
        n[i] = i + 1; 
        if (!digitsSum(n[i], false, true)) go = false;
    }
    if (go){
        for (int i = 1; i < 10000; i++){
            for (int j = i; j > 0 && n[j-1] < n[j]; j--) swap(n[j-1],n[j]);
        }
    }
    for (int i = 0; i < 10000; i++) std::cout<<n[i]<<" , ";
}
void task2(){
    int n[1000]{0};
    for (int i = 0; i < 1000; i++) n[i] = i + 1;
    for (int i = 1; i < 1000; i++){
        for (int j = i; j > 0; j--){
            if (digitsSum(n[j], false, false) == digitsSum(n[j-1], false, false)){
                if (digitsSum(n[j], true, false) == digitsSum(n[j-1], true, false)){
                    n[j-1] > n[j] ? swap(n[j-1], n[j]) : j--;
                }
                else digitsSum(n[j-1], true, false) > digitsSum(n[j], true, false) ? swap(n[j-1], n[j]) : j--;
            }
            else digitsSum(n[j-1], false, false) > digitsSum(n[j], false, false) ? swap(n[j-1], n[j]) : j--;
        }
    }
    for (int i = 0; i < 1000; i++) std::cout<<n[i]<<" , ";
}
void task3(){
    int n[100][100]{}, sum[100]{0}, index{}, max_el{0};
    // заполнение матрицы рандомными числами
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++) n[i][j] = distribution(generator);
    }
    // сумма элементов каждой строки
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            sum[i] += n[i][j];
        }
    }
    // индекс элемента с максимальной суммой
    for (int i = 0; i < 100; i++) max_el = std::max(max_el, sum[i]);
    // индекс строки с максимальной суммой
    for (int i = 0; i < 100; i++) if (sum[i] == max_el){
        index = i; break;
    }
    // строка с максимальной суммой !ВЫВОД!
    for (int i = 0; i < 100; i++){
        if (i == index) {
            for (int j = 0; j < 100; j++){
                std::cout<<n[i][j]<<" , ";
            }
            std::cout<<endl;
        }
    }
    // преобразование строки с максимальной суммой
    for (int i = 0; i < 100; i++){
        if (i == index){
            for (int j = 0; j < 100; j++){
                n[i][j] += 1;
            }
        }
    }
    // преобразованная строка с максимальной суммой !ВЫВОД!
    for (int i = 0; i < 100; i++){
        if (i == index) {
            for (int j = 0; j < 100; j++){
                std::cout<<n[i][j]<<" , ";
            }
        }
    }
}
bool isPalindrome(int n){
    if (digitsSum(n, false, false) == digitsSum(n, true, false)) return false; 
    int digit, num, rev = 0;
    num = n;
    do { digit = n % 10; rev = (rev * 10) + digit; n = n / 10; } while (n != 0);
    return rev == num;
}

void task4(){
    std::vector<int> n;
    for (int i = 0; i < 100; i++) n.push_back(i+1);

    for (int i : n) std::cout<<i<<" , ";
    std::cout<<endl;

    for (int i = 0; i < n.size(); i++){
        if (digitsSum(n[i], false, false) == 10){
            n.erase(n.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < n.size(); i++){
        if (isPalindrome(n[i])) {
            n.insert(n.begin() + i, n[i]);
            i+=2;
        }
    }

    for (int i : n) std::cout<<i<<" , ";
}

int main(){
    // varian 7
    task1();
    //task2();
    //task3();
    //task4();
}
