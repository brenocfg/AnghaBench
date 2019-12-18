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
typedef  int bitmapword ;
struct TYPE_4__ {int* words; int recheck; scalar_t__ ischunk; scalar_t__ blockno; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  TYPE_1__ PagetableEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BITS_PER_BITMAPWORD ; 
 int WORDS_PER_CHUNK ; 
 int WORDS_PER_PAGE ; 
 TYPE_1__* tbm_find_pageentry (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ tbm_page_is_lossy (int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static bool
tbm_intersect_page(TIDBitmap *a, PagetableEntry *apage, const TIDBitmap *b)
{
	const PagetableEntry *bpage;
	int			wordnum;

	if (apage->ischunk)
	{
		/* Scan each bit in chunk, try to clear */
		bool		candelete = true;

		for (wordnum = 0; wordnum < WORDS_PER_CHUNK; wordnum++)
		{
			bitmapword	w = apage->words[wordnum];

			if (w != 0)
			{
				bitmapword	neww = w;
				BlockNumber pg;
				int			bitnum;

				pg = apage->blockno + (wordnum * BITS_PER_BITMAPWORD);
				bitnum = 0;
				while (w != 0)
				{
					if (w & 1)
					{
						if (!tbm_page_is_lossy(b, pg) &&
							tbm_find_pageentry(b, pg) == NULL)
						{
							/* Page is not in b at all, lose lossy bit */
							neww &= ~((bitmapword) 1 << bitnum);
						}
					}
					pg++;
					bitnum++;
					w >>= 1;
				}
				apage->words[wordnum] = neww;
				if (neww != 0)
					candelete = false;
			}
		}
		return candelete;
	}
	else if (tbm_page_is_lossy(b, apage->blockno))
	{
		/*
		 * Some of the tuples in 'a' might not satisfy the quals for 'b', but
		 * because the page 'b' is lossy, we don't know which ones. Therefore
		 * we mark 'a' as requiring rechecks, to indicate that at most those
		 * tuples set in 'a' are matches.
		 */
		apage->recheck = true;
		return false;
	}
	else
	{
		bool		candelete = true;

		bpage = tbm_find_pageentry(b, apage->blockno);
		if (bpage != NULL)
		{
			/* Both pages are exact, merge at the bit level */
			Assert(!bpage->ischunk);
			for (wordnum = 0; wordnum < WORDS_PER_PAGE; wordnum++)
			{
				apage->words[wordnum] &= bpage->words[wordnum];
				if (apage->words[wordnum] != 0)
					candelete = false;
			}
			apage->recheck |= bpage->recheck;
		}
		/* If there is no matching b page, we can just delete the a page */
		return candelete;
	}
}