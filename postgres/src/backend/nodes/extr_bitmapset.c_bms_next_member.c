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
 scalar_t__ bmw_rightmost_one_pos (int) ; 

int
bms_next_member(const Bitmapset *a, int prevbit)
{
	int			nwords;
	int			wordnum;
	bitmapword	mask;

	if (a == NULL)
		return -2;
	nwords = a->nwords;
	prevbit++;
	mask = (~(bitmapword) 0) << BITNUM(prevbit);
	for (wordnum = WORDNUM(prevbit); wordnum < nwords; wordnum++)
	{
		bitmapword	w = a->words[wordnum];

		/* ignore bits before prevbit */
		w &= mask;

		if (w != 0)
		{
			int			result;

			result = wordnum * BITS_PER_BITMAPWORD;
			result += bmw_rightmost_one_pos(w);
			return result;
		}

		/* in subsequent words, consider all bits */
		mask = (~(bitmapword) 0);
	}
	return -2;
}