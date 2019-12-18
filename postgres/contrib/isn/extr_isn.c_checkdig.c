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
 scalar_t__ isdigit (unsigned char) ; 

__attribute__((used)) static unsigned
checkdig(char *num, unsigned size)
{
	unsigned	check = 0,
				check3 = 0;
	unsigned	pos = 0;

	if (*num == 'M')
	{							/* ISMN start with 'M' */
		check3 = 3;
		pos = 1;
	}
	while (*num && size > 1)
	{
		if (isdigit((unsigned char) *num))
		{
			if (pos++ % 2)
				check3 += *num - '0';
			else
				check += *num - '0';
			size--;
		}
		num++;
	}
	check = (check + 3 * check3) % 10;
	if (check != 0)
		check = 10 - check;
	return check;
}