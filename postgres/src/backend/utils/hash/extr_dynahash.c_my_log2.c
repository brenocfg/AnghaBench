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
 int LONG_MAX ; 

int
my_log2(long num)
{
	int			i;
	long		limit;

	/* guard against too-large input, which would put us into infinite loop */
	if (num > LONG_MAX / 2)
		num = LONG_MAX / 2;

	for (i = 0, limit = 1; limit < num; i++, limit <<= 1)
		;
	return i;
}