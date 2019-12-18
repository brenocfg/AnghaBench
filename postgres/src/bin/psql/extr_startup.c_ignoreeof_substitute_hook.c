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
 int /*<<< orphan*/  ParseVariableNum (char*,int /*<<< orphan*/ *,int*) ; 
 char* pg_strdup (char*) ; 

__attribute__((used)) static char *
ignoreeof_substitute_hook(char *newval)
{
	int			dummy;

	/*
	 * This tries to mimic the behavior of bash, to wit "If set, the value is
	 * the number of consecutive EOF characters which must be typed as the
	 * first characters on an input line before bash exits.  If the variable
	 * exists but does not have a numeric value, or has no value, the default
	 * value is 10.  If it does not exist, EOF signifies the end of input to
	 * the shell."  Unlike bash, however, we insist on the stored value
	 * actually being a valid integer.
	 */
	if (newval == NULL)
		newval = pg_strdup("0");
	else if (!ParseVariableNum(newval, NULL, &dummy))
		newval = pg_strdup("10");
	return newval;
}