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
 char* skipcomment (char const*) ; 

__attribute__((used)) static const char *
skipargs(const char *cp)
{
	const char *ocp = cp;
	int level = 0;
	cp = skipcomment(cp);
	if (*cp != '(')
		return (cp);
	do {
		if (*cp == '(')
			level++;
		if (*cp == ')')
			level--;
		cp = skipcomment(cp+1);
	} while (level != 0 && *cp != '\0');
	if (level == 0)
		return (cp);
	else
	/* Rewind and re-detect the syntax error later. */
		return (ocp);
}