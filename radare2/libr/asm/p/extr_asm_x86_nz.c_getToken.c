#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  x86newTokenType ;
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  TT_EOF ; 
 int /*<<< orphan*/  TT_NUMBER ; 
 int /*<<< orphan*/  TT_SPECIAL ; 
 int /*<<< orphan*/  TT_WORD ; 
 scalar_t__ isalnum (int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static x86newTokenType getToken(const char *str, size_t *begin, size_t *end) {
	if (*begin > strlen (str)) {
		return TT_EOF;
	}
	// Skip whitespace
	while (begin && str[*begin] && isspace ((ut8)str[*begin])) {
		++(*begin);
	}

	if (!str[*begin]) {                // null byte
		*end = *begin;
		return TT_EOF;
	}
	if (isalpha ((ut8)str[*begin])) {   // word token
		*end = *begin;
		while (end && str[*end] && isalnum ((ut8)str[*end])) {
			++(*end);
		}
		return TT_WORD;
	}
	if (isdigit ((ut8)str[*begin])) {   // number token
		*end = *begin;
		while (end && isalnum ((ut8)str[*end])) {     // accept alphanumeric characters, because hex.
			++(*end);
		}
		return TT_NUMBER;
	} else {                             // special character: [, ], +, *, ...
		*end = *begin + 1;
		return TT_SPECIAL;
	}
}