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

__attribute__((used)) static int
count_comma_separated_elems(const char *input)
{
	int			n;

	n = 1;
	for (; *input != '\0'; input++)
	{
		if (*input == ',')
			n++;
	}

	return n;
}