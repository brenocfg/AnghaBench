#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bitmapword ;
struct TYPE_3__ {int nwords; scalar_t__* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 scalar_t__ bmw_popcount (scalar_t__) ; 

int
bms_num_members(const Bitmapset *a)
{
	int			result = 0;
	int			nwords;
	int			wordnum;

	if (a == NULL)
		return 0;
	nwords = a->nwords;
	for (wordnum = 0; wordnum < nwords; wordnum++)
	{
		bitmapword	w = a->words[wordnum];

		/* No need to count the bits in a zero word */
		if (w != 0)
			result += bmw_popcount(w);
	}
	return result;
}