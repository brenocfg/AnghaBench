#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offset; int /*<<< orphan*/  tuple; scalar_t__ isDelete; } ;
typedef  TYPE_1__ ginxlogInsertEntry ;
struct TYPE_5__ {int /*<<< orphan*/  relNode; int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
typedef  TYPE_2__ RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetTag (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinSetDownlink (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ginRedoInsertEntry(Buffer buffer, bool isLeaf, BlockNumber rightblkno, void *rdata)
{
	Page		page = BufferGetPage(buffer);
	ginxlogInsertEntry *data = (ginxlogInsertEntry *) rdata;
	OffsetNumber offset = data->offset;
	IndexTuple	itup;

	if (rightblkno != InvalidBlockNumber)
	{
		/* update link to right page after split */
		Assert(!GinPageIsLeaf(page));
		Assert(offset >= FirstOffsetNumber && offset <= PageGetMaxOffsetNumber(page));
		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, offset));
		GinSetDownlink(itup, rightblkno);
	}

	if (data->isDelete)
	{
		Assert(GinPageIsLeaf(page));
		Assert(offset >= FirstOffsetNumber && offset <= PageGetMaxOffsetNumber(page));
		PageIndexTupleDelete(page, offset);
	}

	itup = &data->tuple;

	if (PageAddItem(page, (Item) itup, IndexTupleSize(itup), offset, false, false) == InvalidOffsetNumber)
	{
		RelFileNode node;
		ForkNumber	forknum;
		BlockNumber blknum;

		BufferGetTag(buffer, &node, &forknum, &blknum);
		elog(ERROR, "failed to add item to index page in %u/%u/%u",
			 node.spcNode, node.dbNode, node.relNode);
	}
}