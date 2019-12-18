#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int bitmapword ;
struct TYPE_6__ {int nwords; int* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAPSET_SIZE (int) ; 
 int BITNUM (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int WORDNUM (int) ; 
 TYPE_1__* bms_make_singleton (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ repalloc (TYPE_1__*,int /*<<< orphan*/ ) ; 

Bitmapset *
bms_add_member(Bitmapset *a, int x)
{
	int			wordnum,
				bitnum;

	if (x < 0)
		elog(ERROR, "negative bitmapset member not allowed");
	if (a == NULL)
		return bms_make_singleton(x);
	wordnum = WORDNUM(x);
	bitnum = BITNUM(x);

	/* enlarge the set if necessary */
	if (wordnum >= a->nwords)
	{
		int			oldnwords = a->nwords;
		int			i;

		a = (Bitmapset *) repalloc(a, BITMAPSET_SIZE(wordnum + 1));
		a->nwords = wordnum + 1;
		/* zero out the enlarged portion */
		for (i = oldnwords; i < a->nwords; i++)
			a->words[i] = 0;
	}

	a->words[wordnum] |= ((bitmapword) 1 << bitnum);
	return a;
}