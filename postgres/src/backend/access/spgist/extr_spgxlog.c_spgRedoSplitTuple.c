#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ offnumPrefix; int /*<<< orphan*/  offnumPostfix; scalar_t__ postfixBlkSame; scalar_t__ newPage; } ;
typedef  TYPE_1__ spgxlogSplitTuple ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ SpGistInnerTupleData ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  addOrReplaceTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,char*,int) ; 

__attribute__((used)) static void
spgRedoSplitTuple(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	char	   *ptr = XLogRecGetData(record);
	spgxlogSplitTuple *xldata = (spgxlogSplitTuple *) ptr;
	char	   *prefixTuple;
	SpGistInnerTupleData prefixTupleHdr;
	char	   *postfixTuple;
	SpGistInnerTupleData postfixTupleHdr;
	Buffer		buffer;
	Page		page;
	XLogRedoAction action;

	ptr += sizeof(spgxlogSplitTuple);
	prefixTuple = ptr;
	/* the prefix tuple is unaligned, so make a copy to access its header */
	memcpy(&prefixTupleHdr, prefixTuple, sizeof(SpGistInnerTupleData));
	ptr += prefixTupleHdr.size;
	postfixTuple = ptr;
	/* postfix tuple is also unaligned */
	memcpy(&postfixTupleHdr, postfixTuple, sizeof(SpGistInnerTupleData));

	/*
	 * In normal operation we would have both pages locked simultaneously; but
	 * in WAL replay it should be safe to update them one at a time, as long
	 * as we do it in the right order.
	 */

	/* insert postfix tuple first to avoid dangling link */
	if (!xldata->postfixBlkSame)
	{
		if (xldata->newPage)
		{
			buffer = XLogInitBufferForRedo(record, 1);
			/* SplitTuple is not used for nulls pages */
			SpGistInitBuffer(buffer, 0);
			action = BLK_NEEDS_REDO;
		}
		else
			action = XLogReadBufferForRedo(record, 1, &buffer);
		if (action == BLK_NEEDS_REDO)
		{
			page = BufferGetPage(buffer);

			addOrReplaceTuple(page, (Item) postfixTuple,
							  postfixTupleHdr.size, xldata->offnumPostfix);

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}

	/* now handle the original page */
	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		page = BufferGetPage(buffer);

		PageIndexTupleDelete(page, xldata->offnumPrefix);
		if (PageAddItem(page, (Item) prefixTuple, prefixTupleHdr.size,
						xldata->offnumPrefix, false, false) != xldata->offnumPrefix)
			elog(ERROR, "failed to add item of size %u to SPGiST index page",
				 prefixTupleHdr.size);

		if (xldata->postfixBlkSame)
			addOrReplaceTuple(page, (Item) postfixTuple,
							  postfixTupleHdr.size,
							  xldata->offnumPostfix);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}