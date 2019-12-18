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
 int BITS_PER_BITMAPWORD ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HAS_MULTIPLE_ONES (scalar_t__) ; 
 scalar_t__ bmw_rightmost_one_pos (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

int
bms_singleton_member(const Bitmapset *a)
{
	int			result = -1;
	int			nwords;
	int			wordnum;

	if (a == NULL)
		elog(ERROR, "bitmapset is empty");
	nwords = a->nwords;
	for (wordnum = 0; wordnum < nwords; wordnum++)
	{
		bitmapword	w = a->words[wordnum];

		if (w != 0)
		{
			if (result >= 0 || HAS_MULTIPLE_ONES(w))
				elog(ERROR, "bitmapset has multiple members");
			result = wordnum * BITS_PER_BITMAPWORD;
			result += bmw_rightmost_one_pos(w);
		}
	}
	if (result < 0)
		elog(ERROR, "bitmapset is empty");
	return result;
}