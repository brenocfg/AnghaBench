#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  PageHeader ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;

/* Variables and functions */
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 scalar_t__ MaxHeapTuplesPerPage ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetFreeSpace (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 scalar_t__ PageHasFreeLinePointers (int /*<<< orphan*/ ) ; 

Size
PageGetHeapFreeSpace(Page page)
{
	Size		space;

	space = PageGetFreeSpace(page);
	if (space > 0)
	{
		OffsetNumber offnum,
					nline;

		/*
		 * Are there already MaxHeapTuplesPerPage line pointers in the page?
		 */
		nline = PageGetMaxOffsetNumber(page);
		if (nline >= MaxHeapTuplesPerPage)
		{
			if (PageHasFreeLinePointers((PageHeader) page))
			{
				/*
				 * Since this is just a hint, we must confirm that there is
				 * indeed a free line pointer
				 */
				for (offnum = FirstOffsetNumber; offnum <= nline; offnum = OffsetNumberNext(offnum))
				{
					ItemId		lp = PageGetItemId(page, offnum);

					if (!ItemIdIsUsed(lp))
						break;
				}

				if (offnum > nline)
				{
					/*
					 * The hint is wrong, but we can't clear it here since we
					 * don't have the ability to mark the page dirty.
					 */
					space = 0;
				}
			}
			else
			{
				/*
				 * Although the hint might be wrong, PageAddItem will believe
				 * it anyway, so we must believe it too.
				 */
				space = 0;
			}
		}
	}
	return space;
}