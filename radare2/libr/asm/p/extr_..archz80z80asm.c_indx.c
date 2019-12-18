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

/* Variables and functions */
 int comma ; 
 char* delspc (char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ isalnum (unsigned char const) ; 
 char mem_delimiter ; 
 int /*<<< orphan*/  rd_comma (char const**) ; 
 int /*<<< orphan*/  rd_expr (char const**,char,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp ; 

__attribute__((used)) static int indx(const char **ptr, const char **list, int error, const char **expr) {
	int i;
	*ptr = delspc (*ptr);
	if (!**ptr) {
		if (error) {
			eprintf ("unexpected end of line\n");
			return 0;
		} else {
			return 0;
		}
	}
	if (comma > 1) {
		rd_comma (ptr);
	}
	for (i = 0; list[i]; i++) {
		const char *input = *ptr;
		const char *check = list[i];
		int had_expr = 0;
		if (!list[i][0]) {
			continue;
		}
		while (*check) {
			if (*check == ' ') {
				input = delspc (input);
			} else if (*check == '*') {
				*expr = input;
				mem_delimiter = check[1];
				rd_expr (&input, mem_delimiter, NULL, sp, 0);
				had_expr = 1;
			} else if (*check == '+') {
				if (*input == '+' || *input == '-') {
					*expr = input;
					mem_delimiter = check[1];
					rd_expr (&input, mem_delimiter, NULL, sp, 0);
				}
			} else if (*check == *input || (*check >= 'a' && *check <= 'z'
							&& *check - 'a' + 'A' == *input)) {
				++input;
			} else {
				break;
			}

			++check;
		}
		if (*check || (isalnum ((const unsigned char) check[-1]) && isalnum ((const unsigned char) input[0]))) {
			continue;
		}
		if (had_expr) {
			input = delspc (input);
			if (*input && *input != ',') {
				continue;
			}
		}
		*ptr = input;
		comma++;
		return i + 1;
	}
	// if (error) eprintf ("parse error. Remainder of line=%s\n", *ptr);
	return 0;
}