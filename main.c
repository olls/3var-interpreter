#include <stdio.h>
#include <math.h>


int main(int argc, char *argv[]) {

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [program]\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Error: file does not exist.\n");
    return 1;
  }

  long int a = 0;
  long int b = 0;
  long int r = 0;

  int cond = 0;
  int loop = 0;
  int i = 0;

  char c;
  while ((c = fgetc(file)) != EOF) {
    switch (c) {
      case 'i': // Increments A
        a++;
        break;

      case 'd': // Decrements A
        a--;
        break;

      case 's': // Squares A
        a *= a;
        break;

      case 'p': // Prints A
        printf("%d", a);
        break;

      case 'P': // Prints the ASCII character associated with A
        printf("%c", a);
        break;

      case 'x': // Sets A to the absolute value of A
        a = abs(a);
        break;

      case '>': // Sets A to R
        a = r;
        break;

      case 'a': // Increments B
        b++;
        break;

      case 'k': // Decrements B
        b--;
        break;

      case 'm': // Squares B
        b *= b;
        break;

      case 'o': // Prints B
        printf("%d", b);
        break;

      case 'O': // Prints the ASCII character of B
        printf("%c", b);
        break;

      case '0': // Sets B to the absolute value of B
        b = abs(b);
        break;

      case '<': // Sets B to R
        b = r;
        break;

      case '+': // Adds A and B, stores in R
        r = a + b;
        break;

      case '-': // Subtracts B from A, stores in R
        r = a - b;
        break;

      case '*': // Multiplies A and B, stores in R
        r = a * b;
        break;


      case '/': // Divides A by B, stores in R
        r = a / b;
        break;

      case '^': // Exponentiates A to the Bth power, stores in R
        r = pow(a, b);
        break;

      case 'w': // Prints R
        printf("%d\n", r);
        break;

      case 'u': // Marks a conditional which executes only if a>b
        cond = a > b;
        break;

      case 'U': // Marks a conditional which executes only if a<b
        cond = a < b;
        break;

      case '=': // Marks a conditional which executes only if a==b
        cond = a == b;
        break;

      case '(': // Starts an if statement body
        if (!cond) {
          while (fgetc(file) != ')');
        }
        break;

      case ')': // Ends an if statement body
        break;

      case '|': // Marks a loop which executes while a>b
        loop = '|';
        break;

      case '_': // Marks a loop which executes while a<b
        loop = '_';
        break;

      case '\\': // Marks a loop which executes while a==b
        loop = '\\';
        break;

      case 'f': // Marks a loop which executes a times
        loop = 'f';
        break;

      case 'F': // Marks a loop which executes B times
        loop = 'F';
        break;

      case '{': // Starts a loop which repeats forever
        break;

      case '}': // Ends a loop which repeats forever
        while (fgetc(file) != '{') {
          fseek(file, -2, SEEK_CUR);
        }
        break;

      case '[': // Starts a marked loop
        i = 0;
        break;

      case ']': // Ends a marked loop
        switch (loop) {
          case '|':
            cond = a > b;
            break;
          case '_':
            cond = a < b;
            break;
          case '\\':
            cond = a == b;
            break;
          case 'f':
            cond = i++ < a;
            break;
          case 'F':
            cond = i++ < b;
            break;
        }
        if (cond) {
          while (fgetc(file) != '[') {
            fseek(file, -2, SEEK_CUR);
          }
        }
        break;

      case '\'': // Takes a 1 character input from the user and stores the ASCII value of the character in R
        r = getchar();
        break;

      case '"': // Takes a number input from the user and stores it in R
        r = getchar() - 48;
        break;

      case 'r': // Resets all variables to 0
        a = 0;
        b = 0;
        r = 0;
        break;

      case '@': // Resets A to 0
        a = 0;
        break;

      case '#': // Rests B to 0
        b = 0;
        break;

      case 'e': // Resets R to 0
        r = 0;
        break;

      case '$': // Toggles comment
        while (fgetc(file) != '$');
        break;

      case '~': // Starts a line comment
        while (fgetc(file) != '\n');
        break;

      case '`': // Causes the interpreter to ignore the next character
        fgetc(file);
        break;

    }
  }

  fclose(file);
  printf("\n");

  return 0;
}