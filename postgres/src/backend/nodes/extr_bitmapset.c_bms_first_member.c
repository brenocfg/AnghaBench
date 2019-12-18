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
typedef  int /*<<< orphan*/  bitmapword ;
struct TYPE_3__ {int nwords; int /*<<< orphan*/ * words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int BITS_PER_BITMAPWORD ; 
 int /*<<< orphan*/  RIGHTMOST_ONE (int /*<<< orphan*/ ) ; 
 scalar_t__ bmw_rightmost_one_pos (int /*<<< orphan*/ ) ; 

int
bms_first_member(Bitmapset *a)
{
	int			nwords;
	int			wordnum;

	if (a == NULL)
		return -1;
	nwords = a->nwords;
	for (wordnum = 0; wordnum < nwords; wordnum++)
	{
		bitmapword	w = a->words[wordnum];

		if (w != 0)
		{
			int			result;

			w = RIGHTMOST_ONE(w);
			a->words[wordnum] &= ~w;

			result = wordnum * BITS_PER_BITMAPWORD;
			result += bmw_rightmost_one_pos(w);
			return result;
		}
	}
	return -1;
}