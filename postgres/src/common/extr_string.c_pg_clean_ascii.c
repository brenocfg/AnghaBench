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

void
pg_clean_ascii(char *str)
{
	/* Only allow clean ASCII chars in the string */
	char	   *p;

	for (p = str; *p != '\0'; p++)
	{
		if (*p < 32 || *p > 126)
			*p = '?';
	}
}