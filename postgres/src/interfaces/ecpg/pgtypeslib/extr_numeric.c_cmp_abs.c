#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int weight; int ndigits; scalar_t__* digits; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */

__attribute__((used)) static int
cmp_abs(numeric *var1, numeric *var2)
{
	int			i1 = 0;
	int			i2 = 0;
	int			w1 = var1->weight;
	int			w2 = var2->weight;
	int			stat;

	while (w1 > w2 && i1 < var1->ndigits)
	{
		if (var1->digits[i1++] != 0)
			return 1;
		w1--;
	}
	while (w2 > w1 && i2 < var2->ndigits)
	{
		if (var2->digits[i2++] != 0)
			return -1;
		w2--;
	}

	if (w1 == w2)
	{
		while (i1 < var1->ndigits && i2 < var2->ndigits)
		{
			stat = var1->digits[i1++] - var2->digits[i2++];
			if (stat)
			{
				if (stat > 0)
					return 1;
				return -1;
			}
		}
	}

	while (i1 < var1->ndigits)
	{
		if (var1->digits[i1++] != 0)
			return 1;
	}
	while (i2 < var2->ndigits)
	{
		if (var2->digits[i2++] != 0)
			return -1;
	}

	return 0;
}