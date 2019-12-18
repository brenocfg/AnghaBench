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
typedef  int /*<<< orphan*/  NumericVar ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ ) ; 
 char* get_str_from_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int strlen (char*) ; 

char *
numeric_normalize(Numeric num)
{
	NumericVar	x;
	char	   *str;
	int			last;

	/*
	 * Handle NaN
	 */
	if (NUMERIC_IS_NAN(num))
		return pstrdup("NaN");

	init_var_from_num(num, &x);

	str = get_str_from_var(&x);

	/* If there's no decimal point, there's certainly nothing to remove. */
	if (strchr(str, '.') != NULL)
	{
		/*
		 * Back up over trailing fractional zeroes.  Since there is a decimal
		 * point, this loop will terminate safely.
		 */
		last = strlen(str) - 1;
		while (str[last] == '0')
			last--;

		/* We want to get rid of the decimal point too, if it's now last. */
		if (str[last] == '.')
			last--;

		/* Delete whatever we backed up over. */
		str[last + 1] = '\0';
	}

	return str;
}