#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ heapBlk; scalar_t__ offnum; int /*<<< orphan*/  pagesPerRange; } ;
typedef  TYPE_1__ xl_brin_insert ;
typedef  scalar_t__ XLogRedoAction ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_11__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_12__ {scalar_t__ bt_blkno; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_3__ BrinTuple ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BRIN_PAGETYPE_REGULAR ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int XLOG_BRIN_INIT_PAGE ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  brinSetHeapBlockItemptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_page_init (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
brin_xlog_insert_update(XLogReaderState *record,
						xl_brin_insert *xlrec)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	Buffer		buffer;
	BlockNumber regpgno;
	Page		page;
	XLogRedoAction action;

	/*
	 * If we inserted the first and only tuple on the page, re-initialize the
	 * page from scratch.
	 */
	if (XLogRecGetInfo(record) & XLOG_BRIN_INIT_PAGE)
	{
		buffer = XLogInitBufferForRedo(record, 0);
		page = BufferGetPage(buffer);
		brin_page_init(page, BRIN_PAGETYPE_REGULAR);
		action = BLK_NEEDS_REDO;
	}
	else
	{
		action = XLogReadBufferForRedo(record, 0, &buffer);
	}

	/* need this page's blkno to store in revmap */
	regpgno = BufferGetBlockNumber(buffer);

	/* insert the index item into the page */
	if (action == BLK_NEEDS_REDO)
	{
		OffsetNumber offnum;
		BrinTuple  *tuple;
		Size		tuplen;

		tuple = (BrinTuple *) XLogRecGetBlockData(record, 0, &tuplen);

		Assert(tuple->bt_blkno == xlrec->heapBlk);

		page = (Page) BufferGetPage(buffer);
		offnum = xlrec->offnum;
		if (PageGetMaxOffsetNumber(page) + 1 < offnum)
			elog(PANIC, "brin_xlog_insert_update: invalid max offset number");

		offnum = PageAddItem(page, (Item) tuple, tuplen, offnum, true, false);
		if (offnum == InvalidOffsetNumber)
			elog(PANIC, "brin_xlog_insert_update: failed to add tuple");

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* update the revmap */
	action = XLogReadBufferForRedo(record, 1, &buffer);
	if (action == BLK_NEEDS_REDO)
	{
		ItemPointerData tid;

		ItemPointerSet(&tid, regpgno, xlrec->offnum);
		page = (Page) BufferGetPage(buffer);

		brinSetHeapBlockItemptr(buffer, xlrec->pagesPerRange, xlrec->heapBlk,
								tid);
		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* XXX no FSM updates here ... */
}