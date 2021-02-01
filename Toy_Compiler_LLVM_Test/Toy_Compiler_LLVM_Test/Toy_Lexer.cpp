#include <iostream>

// If the lexer finds an unknown character it returns it's ASCII value [0-255],
// otherwise it will return the value that is enumerated below.
enum TOKEN {
	// Token for END OF FILE
	TOK_EOF = -1,

	// Commands such as DEFINE and EXTERN
	TOK_DEF = -2,
	TOK_EXTERN = -3,

	// Primary use cases for tokens such as TYPE and VALUE
	TOK_IDENTIFIER = -4,
	TOK_NUMBER = -5,
};

// Global Variables for simplicity, not best option for real language creation.
static std::string G_IDENTIFIER; //Stores result of (if TOK_IDENTIFIER)
static double G_NUMBER;          //Stores result of (if TOK_NUMBER)

// Returns the next token from standard input
static int getToken() {
	// Variable to hold characters
	static int lastChar = ' ';

	// Skips Whitespace
	while (isspace(lastChar)) {
		lastChar = getchar();
	}

	// Lexes for alphabet characters	
	if (isalpha(lastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
		G_IDENTIFIER = lastChar;

		while (isalnum((lastChar = getchar()))) {
			G_IDENTIFIER += lastChar;
		}

		if (G_IDENTIFIER == "define") {
			return TOK_DEF;
		}

		if (G_IDENTIFIER == "extern") {
			return TOK_EXTERN;
		}

		return TOK_IDENTIFIER;

	}

	// Lexes for numerical digits
	if (isdigit(lastChar) || lastChar == '.') {
		std::string numberString;

		do {
			numberString += lastChar;
			lastChar = getchar();
		} while (isdigit(lastChar) || lastChar == '.');

		G_NUMBER = strtod(numberString.c_str(), 0);
		return TOK_NUMBER;
	}

	// Lexes for Comments
	if (lastChar == '#') {
		// Comment until end of line.
		do {
			lastChar = getchar();
		} while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

		if (lastChar != EOF) {
			return getToken();
		}
	}

	// Lexes for End of File
	if (lastChar == EOF) {
		return TOK_EOF;
	}

	// Lexer wasn't able to lex, return the ASCII character of the trouble child.
	int thisChar = lastChar;
	lastChar = getchar();
	return thisChar;
}