#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int bitmapword ;
struct TYPE_5__ {int nwords; int* words; } ;
typedef  TYPE_1__ Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAPSET_SIZE (int) ; 
 int BITNUM (int) ; 
 int BITS_PER_BITMAPWORD ; 
 int /*<<< orphan*/  ERROR ; 
 int WORDNUM (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (TYPE_1__*,int /*<<< orphan*/ ) ; 

Bitmapset *
bms_add_range(Bitmapset *a, int lower, int upper)
{
	int			lwordnum,
				lbitnum,
				uwordnum,
				ushiftbits,
				wordnum;

	/* do nothing if nothing is called for, without further checking */
	if (upper < lower)
		return a;

	if (lower < 0)
		elog(ERROR, "negative bitmapset member not allowed");
	uwordnum = WORDNUM(upper);

	if (a == NULL)
	{
		a = (Bitmapset *) palloc0(BITMAPSET_SIZE(uwordnum + 1));
		a->nwords = uwordnum + 1;
	}
	else if (uwordnum >= a->nwords)
	{
		int			oldnwords = a->nwords;
		int			i;

		/* ensure we have enough words to store the upper bit */
		a = (Bitmapset *) repalloc(a, BITMAPSET_SIZE(uwordnum + 1));
		a->nwords = uwordnum + 1;
		/* zero out the enlarged portion */
		for (i = oldnwords; i < a->nwords; i++)
			a->words[i] = 0;
	}

	wordnum = lwordnum = WORDNUM(lower);

	lbitnum = BITNUM(lower);
	ushiftbits = BITS_PER_BITMAPWORD - (BITNUM(upper) + 1);

	/*
	 * Special case when lwordnum is the same as uwordnum we must perform the
	 * upper and lower masking on the word.
	 */
	if (lwordnum == uwordnum)
	{
		a->words[lwordnum] |= ~(bitmapword) (((bitmapword) 1 << lbitnum) - 1)
			& (~(bitmapword) 0) >> ushiftbits;
	}
	else
	{
		/* turn on lbitnum and all bits left of it */
		a->words[wordnum++] |= ~(bitmapword) (((bitmapword) 1 << lbitnum) - 1);

		/* turn on all bits for any intermediate words */
		while (wordnum < uwordnum)
			a->words[wordnum++] = ~(bitmapword) 0;

		/* turn on upper's bit and all bits right of it. */
		a->words[uwordnum] |= (~(bitmapword) 0) >> ushiftbits;
	}

	return a;
}