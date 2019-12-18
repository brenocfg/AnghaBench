#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ offnumLeaf; scalar_t__ offnumHeadLeaf; scalar_t__ offnumParent; int /*<<< orphan*/  nodeI; scalar_t__ storesNulls; scalar_t__ newPage; } ;
typedef  TYPE_1__ spgxlogAddLeaf ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_12__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_14__ {scalar_t__ nextOffset; } ;
struct TYPE_13__ {scalar_t__ nextOffset; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ SpGistLeafTupleData ;
typedef  TYPE_4__* SpGistLeafTuple ;
typedef  scalar_t__ SpGistInnerTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 int SPGIST_NULLS ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  addOrReplaceTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  spgUpdateNodeLink (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
spgRedoAddLeaf(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogAddLeaf *xldata = (spgxlogAddLeaf *) ptr;
	char	   *leafTuple;
	SpGistLeafTupleData leafTupleHdr;
	Buffer		buffer;
	Page		page;
	XLogRedoAction action;

	ptr += sizeof(spgxlogAddLeaf);
	leafTuple = ptr;
	/* the leaf tuple is unaligned, so make a copy to access its header */
	memcpy(&leafTupleHdr, leafTuple, sizeof(SpGistLeafTupleData));

	/*
	 * In normal operation we would have both current and parent pages locked
	 * simultaneously; but in WAL replay it should be safe to update the leaf
	 * page before updating the parent.
	 */
	if (xldata->newPage)
	{
		buffer = XLogInitBufferForRedo(record, 0);
		SpGistInitBuffer(buffer,
						 SPGIST_LEAF | (xldata->storesNulls ? SPGIST_NULLS : 0));
		action = BLK_NEEDS_REDO;
	}
	else
		action = XLogReadBufferForRedo(record, 0, &buffer);

	if (action == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(buffer);

		/* insert new tuple */
		if (xldata->offnumLeaf != xldata->offnumHeadLeaf)
		{
			/* normal cases, tuple was added by SpGistPageAddNewItem */
			addOrReplaceTuple(page, (Item) leafTuple, leafTupleHdr.size,
							  xldata->offnumLeaf);

			/* update head tuple's chain link if needed */
			if (xldata->offnumHeadLeaf != InvalidOffsetNumber)
			{
				SpGistLeafTuple head;

				head = (SpGistLeafTuple) PageGetItem(page,
													 PageGetItemId(page, xldata->offnumHeadLeaf));
				Assert(head->nextOffset == leafTupleHdr.nextOffset);
				head->nextOffset = xldata->offnumLeaf;
			}
		}
		else
		{
			/* replacing a DEAD tuple */
			PageIndexTupleDelete(page, xldata->offnumLeaf);
			if (PageAddItem(page,
							(Item) leafTuple, leafTupleHdr.size,
							xldata->offnumLeaf, false, false) != xldata->offnumLeaf)
				elog(ERROR, "failed to add item of size %u to SPGiST index page",
					 leafTupleHdr.size);
		}

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* update parent downlink if necessary */
	if (xldata->offnumParent != InvalidOffsetNumber)
	{
		if (XLogReadBufferForRedo(record, 1, &buffer) == BLK_NEEDS_REDO)
		{
			SpGistInnerTuple tuple;
			BlockNumber blknoLeaf;

			XLogRecGetBlockTag(record, 0, NULL, NULL, &blknoLeaf);

			page = BufferGetPage(buffer);

			tuple = (SpGistInnerTuple) PageGetItem(page,
												   PageGetItemId(page, xldata->offnumParent));

			spgUpdateNodeLink(tuple, xldata->nodeI,
							  blknoLeaf, xldata->offnumLeaf);

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}
}