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
get_ten(int b, int *ku)
{
	int			ten;

	if (b >= 0x40 && b <= 0x7e)
	{
		ten = b - 0x3f;
		*ku = 1;
	}
	else if (b >= 0x80 && b <= 0x9e)
	{
		ten = b - 0x40;
		*ku = 1;
	}
	else if (b >= 0x9f && b <= 0xfc)
	{
		ten = b - 0x9e;
		*ku = 0;
	}
	else
	{
		ten = -1;				/* error */
		*ku = 0;				/* keep compiler quiet */
	}
	return ten;
}