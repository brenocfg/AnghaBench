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
struct TYPE_6__ {int /*<<< orphan*/  entryCategory; int /*<<< orphan*/  entryKey; int /*<<< orphan*/  entryAttnum; int /*<<< orphan*/  ginstate; scalar_t__ fullScan; } ;
struct TYPE_5__ {void* off; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  TYPE_2__* GinBtree ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 void* FirstOffsetNumber ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int ginCompareAttEntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gintuple_get_attrnum (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gintuple_get_key (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
entryLocateLeafEntry(GinBtree btree, GinBtreeStack *stack)
{
	Page		page = BufferGetPage(stack->buffer);
	OffsetNumber low,
				high;

	Assert(GinPageIsLeaf(page));
	Assert(!GinPageIsData(page));

	if (btree->fullScan)
	{
		stack->off = FirstOffsetNumber;
		return true;
	}

	low = FirstOffsetNumber;
	high = PageGetMaxOffsetNumber(page);

	if (high < low)
	{
		stack->off = FirstOffsetNumber;
		return false;
	}

	high++;

	while (high > low)
	{
		OffsetNumber mid = low + ((high - low) / 2);
		IndexTuple	itup;
		OffsetNumber attnum;
		Datum		key;
		GinNullCategory category;
		int			result;

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, mid));
		attnum = gintuple_get_attrnum(btree->ginstate, itup);
		key = gintuple_get_key(btree->ginstate, itup, &category);
		result = ginCompareAttEntries(btree->ginstate,
									  btree->entryAttnum,
									  btree->entryKey,
									  btree->entryCategory,
									  attnum, key, category);
		if (result == 0)
		{
			stack->off = mid;
			return true;
		}
		else if (result > 0)
			low = mid + 1;
		else
			high = mid;
	}

	stack->off = high;
	return false;
}