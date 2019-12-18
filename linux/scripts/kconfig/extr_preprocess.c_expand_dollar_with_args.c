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
 char* eval_clause (char const*,int,int,char**) ; 
 int /*<<< orphan*/  pperror (char*,char const*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *expand_dollar_with_args(const char **str, int argc, char *argv[])
{
	const char *p = *str;
	const char *q;
	int nest = 0;

	/*
	 * In Kconfig, variable/function references always start with "$(".
	 * Neither single-letter variables as in $A nor curly braces as in ${CC}
	 * are supported.  '$' not followed by '(' loses its special meaning.
	 */
	if (*p != '(') {
		*str = p;
		return xstrdup("$");
	}

	p++;
	q = p;
	while (*q) {
		if (*q == '(') {
			nest++;
		} else if (*q == ')') {
			if (nest-- == 0)
				break;
		}
		q++;
	}

	if (!*q)
		pperror("unterminated reference to '%s': missing ')'", p);

	/* Advance 'str' to after the expanded initial portion of the string */
	*str = q + 1;

	return eval_clause(p, q - p, argc, argv);
}