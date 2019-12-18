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
 int /*<<< orphan*/  decimal_point ; 
 int groupdigits ; 
 int integer_digits (char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thousands_sep ; 

__attribute__((used)) static int
additional_numeric_locale_len(const char *my_str)
{
	int			int_len = integer_digits(my_str),
				len = 0;

	/* Account for added thousands_sep instances */
	if (int_len > groupdigits)
		len += ((int_len - 1) / groupdigits) * strlen(thousands_sep);

	/* Account for possible additional length of decimal_point */
	if (strchr(my_str, '.') != NULL)
		len += strlen(decimal_point) - 1;

	return len;
}