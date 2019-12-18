#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int bitmapword ;
struct TYPE_6__ {int* words; } ;
struct TYPE_5__ {scalar_t__* offsets; } ;
typedef  TYPE_1__ TBMIterateResult ;
typedef  TYPE_2__ PagetableEntry ;
typedef  scalar_t__ OffsetNumber ;

/* Variables and functions */
 int BITS_PER_BITMAPWORD ; 
 int WORDS_PER_PAGE ; 

__attribute__((used)) static inline int
tbm_extract_page_tuple(PagetableEntry *page, TBMIterateResult *output)
{
	int			wordnum;
	int			ntuples = 0;

	for (wordnum = 0; wordnum < WORDS_PER_PAGE; wordnum++)
	{
		bitmapword	w = page->words[wordnum];

		if (w != 0)
		{
			int			off = wordnum * BITS_PER_BITMAPWORD + 1;

			while (w != 0)
			{
				if (w & 1)
					output->offsets[ntuples++] = (OffsetNumber) off;
				off++;
				w >>= 1;
			}
		}
	}

	return ntuples;
}