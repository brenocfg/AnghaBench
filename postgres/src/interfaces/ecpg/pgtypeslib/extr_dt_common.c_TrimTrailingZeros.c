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
 int strlen (char*) ; 

void
TrimTrailingZeros(char *str)
{
	int			len = strlen(str);

	/* chop off trailing zeros... but leave at least 2 fractional digits */
	while (*(str + len - 1) == '0' && *(str + len - 3) != '.')
	{
		len--;
		*(str + len) = '\0';
	}
}