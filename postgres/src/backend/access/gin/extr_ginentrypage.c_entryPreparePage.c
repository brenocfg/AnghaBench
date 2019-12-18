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
struct TYPE_3__ {int entry; scalar_t__ isDelete; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GinBtreeEntryInsertData ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinSetDownlink (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
entryPreparePage(GinBtree btree, Page page, OffsetNumber off,
				 GinBtreeEntryInsertData *insertData, BlockNumber updateblkno)
{
	Assert(insertData->entry);
	Assert(!GinPageIsData(page));

	if (insertData->isDelete)
	{
		Assert(GinPageIsLeaf(page));
		PageIndexTupleDelete(page, off);
	}

	if (!GinPageIsLeaf(page) && updateblkno != InvalidBlockNumber)
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, off));

		GinSetDownlink(itup, updateblkno);
	}
}