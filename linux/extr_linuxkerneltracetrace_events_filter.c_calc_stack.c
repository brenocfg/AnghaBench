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
 int MISSING_QUOTE ; 
 int TOO_MANY_CLOSE ; 
 int TOO_MANY_OPEN ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static int calc_stack(const char *str, int *parens, int *preds, int *err)
{
	bool is_pred = false;
	int nr_preds = 0;
	int open = 1; /* Count the expression as "(E)" */
	int last_quote = 0;
	int max_open = 1;
	int quote = 0;
	int i;

	*err = 0;

	for (i = 0; str[i]; i++) {
		if (isspace(str[i]))
			continue;
		if (quote) {
			if (str[i] == quote)
			       quote = 0;
			continue;
		}

		switch (str[i]) {
		case '\'':
		case '"':
			quote = str[i];
			last_quote = i;
			break;
		case '|':
		case '&':
			if (str[i+1] != str[i])
				break;
			is_pred = false;
			continue;
		case '(':
			is_pred = false;
			open++;
			if (open > max_open)
				max_open = open;
			continue;
		case ')':
			is_pred = false;
			if (open == 1) {
				*err = i;
				return TOO_MANY_CLOSE;
			}
			open--;
			continue;
		}
		if (!is_pred) {
			nr_preds++;
			is_pred = true;
		}
	}

	if (quote) {
		*err = last_quote;
		return MISSING_QUOTE;
	}

	if (open != 1) {
		int level = open;

		/* find the bad open */
		for (i--; i; i--) {
			if (quote) {
				if (str[i] == quote)
					quote = 0;
				continue;
			}
			switch (str[i]) {
			case '(':
				if (level == open) {
					*err = i;
					return TOO_MANY_OPEN;
				}
				level--;
				break;
			case ')':
				level++;
				break;
			case '\'':
			case '"':
				quote = str[i];
				break;
			}
		}
		/* First character is the '(' with missing ')' */
		*err = 0;
		return TOO_MANY_OPEN;
	}

	/* Set the size of the required stacks */
	*parens = max_open;
	*preds = nr_preds;
	return 0;
}