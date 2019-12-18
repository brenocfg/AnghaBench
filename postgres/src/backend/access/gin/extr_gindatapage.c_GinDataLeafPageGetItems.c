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
struct TYPE_6__ {int /*<<< orphan*/  first; } ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_1__ GinPostingList ;

/* Variables and functions */
 TYPE_1__* GinDataLeafPageGetPostingList (int /*<<< orphan*/ ) ; 
 scalar_t__ GinDataLeafPageGetPostingListSize (int /*<<< orphan*/ ) ; 
 TYPE_1__* GinNextPostingListSegment (TYPE_1__*) ; 
 scalar_t__ GinPageIsCompressed (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dataLeafPageGetUncompressed (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ginPostingListDecodeAllSegments (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 

ItemPointer
GinDataLeafPageGetItems(Page page, int *nitems, ItemPointerData advancePast)
{
	ItemPointer result;

	if (GinPageIsCompressed(page))
	{
		GinPostingList *seg = GinDataLeafPageGetPostingList(page);
		Size		len = GinDataLeafPageGetPostingListSize(page);
		Pointer		endptr = ((Pointer) seg) + len;
		GinPostingList *next;

		/* Skip to the segment containing advancePast+1 */
		if (ItemPointerIsValid(&advancePast))
		{
			next = GinNextPostingListSegment(seg);
			while ((Pointer) next < endptr &&
				   ginCompareItemPointers(&next->first, &advancePast) <= 0)
			{
				seg = next;
				next = GinNextPostingListSegment(seg);
			}
			len = endptr - (Pointer) seg;
		}

		if (len > 0)
			result = ginPostingListDecodeAllSegments(seg, len, nitems);
		else
		{
			result = NULL;
			*nitems = 0;
		}
	}
	else
	{
		ItemPointer tmp = dataLeafPageGetUncompressed(page, nitems);

		result = palloc((*nitems) * sizeof(ItemPointerData));
		memcpy(result, tmp, (*nitems) * sizeof(ItemPointerData));
	}

	return result;
}