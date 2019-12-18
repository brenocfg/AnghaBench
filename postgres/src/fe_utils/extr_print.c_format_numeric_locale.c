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
 int /*<<< orphan*/  Assert (int) ; 
 int additional_numeric_locale_len (char const*) ; 
 char* decimal_point ; 
 int groupdigits ; 
 int integer_digits (char const*) ; 
 char* pg_malloc (int) ; 
 char* pg_strdup (char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int strspn (char const*,char*) ; 
 char* thousands_sep ; 

__attribute__((used)) static char *
format_numeric_locale(const char *my_str)
{
	char	   *new_str;
	int			new_len,
				int_len,
				leading_digits,
				i,
				new_str_pos;

	/*
	 * If the string doesn't look like a number, return it unchanged.  This
	 * check is essential to avoid mangling already-localized "money" values.
	 */
	if (strspn(my_str, "0123456789+-.eE") != strlen(my_str))
		return pg_strdup(my_str);

	new_len = strlen(my_str) + additional_numeric_locale_len(my_str);
	new_str = pg_malloc(new_len + 1);
	new_str_pos = 0;
	int_len = integer_digits(my_str);

	/* number of digits in first thousands group */
	leading_digits = int_len % groupdigits;
	if (leading_digits == 0)
		leading_digits = groupdigits;

	/* process sign */
	if (my_str[0] == '-' || my_str[0] == '+')
	{
		new_str[new_str_pos++] = my_str[0];
		my_str++;
	}

	/* process integer part of number */
	for (i = 0; i < int_len; i++)
	{
		/* Time to insert separator? */
		if (i > 0 && --leading_digits == 0)
		{
			strcpy(&new_str[new_str_pos], thousands_sep);
			new_str_pos += strlen(thousands_sep);
			leading_digits = groupdigits;
		}
		new_str[new_str_pos++] = my_str[i];
	}

	/* handle decimal point if any */
	if (my_str[i] == '.')
	{
		strcpy(&new_str[new_str_pos], decimal_point);
		new_str_pos += strlen(decimal_point);
		i++;
	}

	/* copy the rest (fractional digits and/or exponent, and \0 terminator) */
	strcpy(&new_str[new_str_pos], &my_str[i]);

	/* assert we didn't underestimate new_len (an overestimate is OK) */
	Assert(strlen(new_str) <= new_len);

	return new_str;
}