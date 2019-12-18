#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* getLeftMostChild ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  entryCategory; int /*<<< orphan*/  entryKey; int /*<<< orphan*/  entryAttnum; int /*<<< orphan*/  ginstate; scalar_t__ fullScan; } ;
struct TYPE_6__ {int off; int predictNumber; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  TYPE_2__* GinBtree ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int FirstOffsetNumber ; 
 scalar_t__ GIN_ROOT_BLKNO ; 
 scalar_t__ GinGetDownlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int) ; 
 int PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int ginCompareAttEntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gintuple_get_attrnum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gintuple_get_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BlockNumber
entryLocateEntry(GinBtree btree, GinBtreeStack *stack)
{
	OffsetNumber low,
				high,
				maxoff;
	IndexTuple	itup = NULL;
	int			result;
	Page		page = BufferGetPage(stack->buffer);

	Assert(!GinPageIsLeaf(page));
	Assert(!GinPageIsData(page));

	if (btree->fullScan)
	{
		stack->off = FirstOffsetNumber;
		stack->predictNumber *= PageGetMaxOffsetNumber(page);
		return btree->getLeftMostChild(btree, page);
	}

	low = FirstOffsetNumber;
	maxoff = high = PageGetMaxOffsetNumber(page);
	Assert(high >= low);

	high++;

	while (high > low)
	{
		OffsetNumber mid = low + ((high - low) / 2);

		if (mid == maxoff && GinPageRightMost(page))
		{
			/* Right infinity */
			result = -1;
		}
		else
		{
			OffsetNumber attnum;
			Datum		key;
			GinNullCategory category;

			itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, mid));
			attnum = gintuple_get_attrnum(btree->ginstate, itup);
			key = gintuple_get_key(btree->ginstate, itup, &category);
			result = ginCompareAttEntries(btree->ginstate,
										  btree->entryAttnum,
										  btree->entryKey,
										  btree->entryCategory,
										  attnum, key, category);
		}

		if (result == 0)
		{
			stack->off = mid;
			Assert(GinGetDownlink(itup) != GIN_ROOT_BLKNO);
			return GinGetDownlink(itup);
		}
		else if (result > 0)
			low = mid + 1;
		else
			high = mid;
	}

	Assert(high >= FirstOffsetNumber && high <= maxoff);

	stack->off = high;
	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, high));
	Assert(GinGetDownlink(itup) != GIN_ROOT_BLKNO);
	return GinGetDownlink(itup);
}