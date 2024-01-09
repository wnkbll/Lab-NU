#include <iostream>
#include <cmath>

using namespace std;

const double epsilon = 1e-6;


struct solution {
    double answer;
    int counter;
};


double F(double x) {
    return 3 * sin(sqrt(x)) + 0.35 * x - 3.8;
}


double firstDeritativeToF(double x) {
    return 1.5 * (cos(sqrt(x)) / sqrt(x)) + 0.35;
}


double secondDeritativeToF(double x) {
    return -((3 * sqrt(x) * sin(sqrt(x)) + 4 * cos(sqrt(x))) / 4 * x * x);
}


double F1(double x) {
    return (3 * sin(sqrt(x)) - 3.8) / (-0.35);
}


double firstDeritativeToF1(double x) {
    return 1.5 * (cos(sqrt(x)) / sqrt(x));
}


solution binary() {
    double a = 2, b = 3, xm;
    int counter = 0;

    while (abs(a - b) > epsilon) {
        ++counter;

        xm = (a + b) / 2;

        if (F(b) * F(xm) > 0) {
            b = xm;
        } else {
            a = xm;
        }
    }

    return { (a + b) / 2, counter };
}


solution iteration() {
    double a = 2, b = 3, difference = 1, x_previous, x_current;
    int counter = 0;
    
    if (firstDeritativeToF1(a) < 1) {
        x_previous = a;
    } else if (firstDeritativeToF1(b) < 1) {
        x_previous = b;
    }

    while (difference > epsilon) {
        ++counter;

        x_current = F1(x_previous);

        difference = abs(x_current - x_previous);

        x_previous = x_current;
    }

    return { x_current, counter };
}


solution newton() {
    double a = 2, b = 3, difference = 1, x_previous, x_current;
    int counter = 0;

    if (F(a) * secondDeritativeToF(a) > 0) {
        x_current = a;
    } else if (F(b) * secondDeritativeToF(b) > 0) {
        x_current = b;
    }

    while (difference > epsilon) {
        ++counter;

        x_previous = x_current;

        x_current = x_previous - F(x_previous) / firstDeritativeToF(x_previous);

        difference = abs(x_previous - x_current);
    }

    return { x_current, counter };
}


int main(int argc, char **argv) {
    solution binarySolution = binary();
    solution iterationSolution = iteration();
    solution newtonSolution = newton();

    cout << "Method: binary; x = " <<  binarySolution.answer << "; " << "Amount of iterations = " << binarySolution.counter << endl;

    cout << "Method: iteration; x = " <<  iterationSolution.answer << "; " << "Amount of iterations = " << iterationSolution.counter << endl;

    cout << "Method: Newton; x = " <<  newtonSolution.answer << "; " << "Amount of iterations = " << newtonSolution.counter << endl;

    return 0;
}
