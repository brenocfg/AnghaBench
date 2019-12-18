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
typedef  int bitmapword ;
struct TYPE_3__ {int nwords; int* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int BITNUM (int) ; 
 int BITS_PER_BITMAPWORD ; 
 int WORDNUM (int) ; 
 scalar_t__ bmw_leftmost_one_pos (int) ; 

int
bms_prev_member(const Bitmapset *a, int prevbit)
{
	int			wordnum;
	int			ushiftbits;
	bitmapword	mask;

	/*
	 * If set is NULL or if there are no more bits to the right then we've
	 * nothing to do.
	 */
	if (a == NULL || prevbit == 0)
		return -2;

	/* transform -1 to the highest possible bit we could have set */
	if (prevbit == -1)
		prevbit = a->nwords * BITS_PER_BITMAPWORD - 1;
	else
		prevbit--;

	ushiftbits = BITS_PER_BITMAPWORD - (BITNUM(prevbit) + 1);
	mask = (~(bitmapword) 0) >> ushiftbits;
	for (wordnum = WORDNUM(prevbit); wordnum >= 0; wordnum--)
	{
		bitmapword	w = a->words[wordnum];

		/* mask out bits left of prevbit */
		w &= mask;

		if (w != 0)
		{
			int			result;

			result = wordnum * BITS_PER_BITMAPWORD;
			result += bmw_leftmost_one_pos(w);
			return result;
		}

		/* in subsequent words, consider all bits */
		mask = (~(bitmapword) 0);
	}
	return -2;
}