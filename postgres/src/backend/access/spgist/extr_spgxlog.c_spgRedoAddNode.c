#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_18__ {int parentBlk; scalar_t__ offnum; int /*<<< orphan*/  offnumNew; int /*<<< orphan*/  nodeI; int /*<<< orphan*/  offnumParent; scalar_t__ newPage; int /*<<< orphan*/  stateSrc; } ;
typedef  TYPE_1__ spgxlogAddNode ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_19__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_22__ {int /*<<< orphan*/  size; } ;
struct TYPE_21__ {int /*<<< orphan*/  size; } ;
struct TYPE_20__ {scalar_t__ isBuild; } ;
struct TYPE_17__ {int /*<<< orphan*/  nRedirection; int /*<<< orphan*/  nPlaceholder; } ;
typedef  TYPE_3__ SpGistState ;
typedef  TYPE_4__ SpGistInnerTupleData ;
typedef  scalar_t__ SpGistInnerTuple ;
typedef  TYPE_5__* SpGistDeadTuple ;
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
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPGIST_PLACEHOLDER ; 
 int /*<<< orphan*/  SPGIST_REDIRECT ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_16__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  XLogRecHasBlockRef (TYPE_2__*,int) ; 
 int /*<<< orphan*/  addOrReplaceTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillFakeState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 TYPE_5__* spgFormDeadTuple (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgUpdateNodeLink (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spgRedoAddNode(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogAddNode *xldata = (spgxlogAddNode *) ptr;
	char	   *innerTuple;
	SpGistInnerTupleData innerTupleHdr;
	SpGistState state;
	Buffer		buffer;
	Page		page;
	XLogRedoAction action;

	ptr += sizeof(spgxlogAddNode);
	innerTuple = ptr;
	/* the tuple is unaligned, so make a copy to access its header */
	memcpy(&innerTupleHdr, innerTuple, sizeof(SpGistInnerTupleData));

	fillFakeState(&state, xldata->stateSrc);

	if (!XLogRecHasBlockRef(record, 1))
	{
		/* update in place */
		Assert(xldata->parentBlk == -1);
		if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
		{
			page = BufferGetPage(buffer);

			PageIndexTupleDelete(page, xldata->offnum);
			if (PageAddItem(page, (Item) innerTuple, innerTupleHdr.size,
							xldata->offnum,
							false, false) != xldata->offnum)
				elog(ERROR, "failed to add item of size %u to SPGiST index page",
					 innerTupleHdr.size);

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}
	else
	{
		BlockNumber blkno;
		BlockNumber blknoNew;

		XLogRecGetBlockTag(record, 0, NULL, NULL, &blkno);
		XLogRecGetBlockTag(record, 1, NULL, NULL, &blknoNew);

		/*
		 * In normal operation we would have all three pages (source, dest,
		 * and parent) locked simultaneously; but in WAL replay it should be
		 * safe to update them one at a time, as long as we do it in the right
		 * order. We must insert the new tuple before replacing the old tuple
		 * with the redirect tuple.
		 */

		/* Install new tuple first so redirect is valid */
		if (xldata->newPage)
		{
			/* AddNode is not used for nulls pages */
			buffer = XLogInitBufferForRedo(record, 1);
			SpGistInitBuffer(buffer, 0);
			action = BLK_NEEDS_REDO;
		}
		else
			action = XLogReadBufferForRedo(record, 1, &buffer);
		if (action == BLK_NEEDS_REDO)
		{
			page = BufferGetPage(buffer);

			addOrReplaceTuple(page, (Item) innerTuple,
							  innerTupleHdr.size, xldata->offnumNew);

			/*
			 * If parent is in this same page, update it now.
			 */
			if (xldata->parentBlk == 1)
			{
				SpGistInnerTuple parentTuple;

				parentTuple = (SpGistInnerTuple) PageGetItem(page,
															 PageGetItemId(page, xldata->offnumParent));

				spgUpdateNodeLink(parentTuple, xldata->nodeI,
								  blknoNew, xldata->offnumNew);
			}
			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);

		/* Delete old tuple, replacing it with redirect or placeholder tuple */
		if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
		{
			SpGistDeadTuple dt;

			page = BufferGetPage(buffer);

			if (state.isBuild)
				dt = spgFormDeadTuple(&state, SPGIST_PLACEHOLDER,
									  InvalidBlockNumber,
									  InvalidOffsetNumber);
			else
				dt = spgFormDeadTuple(&state, SPGIST_REDIRECT,
									  blknoNew,
									  xldata->offnumNew);

			PageIndexTupleDelete(page, xldata->offnum);
			if (PageAddItem(page, (Item) dt, dt->size,
							xldata->offnum,
							false, false) != xldata->offnum)
				elog(ERROR, "failed to add item of size %u to SPGiST index page",
					 dt->size);

			if (state.isBuild)
				SpGistPageGetOpaque(page)->nPlaceholder++;
			else
				SpGistPageGetOpaque(page)->nRedirection++;

			/*
			 * If parent is in this same page, update it now.
			 */
			if (xldata->parentBlk == 0)
			{
				SpGistInnerTuple parentTuple;

				parentTuple = (SpGistInnerTuple) PageGetItem(page,
															 PageGetItemId(page, xldata->offnumParent));

				spgUpdateNodeLink(parentTuple, xldata->nodeI,
								  blknoNew, xldata->offnumNew);
			}
			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);

		/*
		 * Update parent downlink (if we didn't do it as part of the source or
		 * destination page update already).
		 */
		if (xldata->parentBlk == 2)
		{
			if (XLogReadBufferForRedo(record, 2, &buffer) == BLK_NEEDS_REDO)
			{
				SpGistInnerTuple parentTuple;

				page = BufferGetPage(buffer);

				parentTuple = (SpGistInnerTuple) PageGetItem(page,
															 PageGetItemId(page, xldata->offnumParent));

				spgUpdateNodeLink(parentTuple, xldata->nodeI,
								  blknoNew, xldata->offnumNew);

				PageSetLSN(page, lsn);
				MarkBufferDirty(buffer);
			}
			if (BufferIsValid(buffer))
				UnlockReleaseBuffer(buffer);
		}
	}
}