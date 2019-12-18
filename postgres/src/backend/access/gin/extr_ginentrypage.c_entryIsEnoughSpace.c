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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int IndexTuple ;
typedef  TYPE_1__ GinBtreeEntryInsertData ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (int) ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
entryIsEnoughSpace(GinBtree btree, Buffer buf, OffsetNumber off,
				   GinBtreeEntryInsertData *insertData)
{
	Size		releasedsz = 0;
	Size		addedsz;
	Page		page = BufferGetPage(buf);

	Assert(insertData->entry);
	Assert(!GinPageIsData(page));

	if (insertData->isDelete)
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, off));

		releasedsz = MAXALIGN(IndexTupleSize(itup)) + sizeof(ItemIdData);
	}

	addedsz = MAXALIGN(IndexTupleSize(insertData->entry)) + sizeof(ItemIdData);

	if (PageGetFreeSpace(page) + releasedsz >= addedsz)
		return true;

	return false;
}