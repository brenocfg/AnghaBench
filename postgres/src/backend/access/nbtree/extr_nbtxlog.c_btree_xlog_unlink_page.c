#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ leftsib; scalar_t__ rightsib; int /*<<< orphan*/  topparent; scalar_t__ leafrightsib; scalar_t__ leafleftsib; int /*<<< orphan*/  btpo_xact; } ;
typedef  TYPE_2__ xl_btree_unlink_page ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_16__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_3__ XLogReaderState ;
struct TYPE_14__ {scalar_t__ level; int /*<<< orphan*/  xact; } ;
struct TYPE_18__ {int btpo_flags; scalar_t__ btpo_cycleid; TYPE_1__ btpo; scalar_t__ btpo_next; scalar_t__ btpo_prev; } ;
struct TYPE_17__ {int t_info; } ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_4__ IndexTupleData ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_5__* BTPageOpaque ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int BTP_DELETED ; 
 int BTP_HALF_DEAD ; 
 int BTP_LEAF ; 
 int /*<<< orphan*/  BTreeTupleSetTopParent (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  P_HIKEY ; 
 scalar_t__ P_NONE ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ XLOG_BTREE_UNLINK_PAGE_META ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_3__*,int) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_3__*) ; 
 scalar_t__ XLogRecHasBlockRef (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _bt_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_restore_meta (TYPE_3__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
btree_xlog_unlink_page(uint8 info, XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_btree_unlink_page *xlrec = (xl_btree_unlink_page *) XLogRecGetData(record);
	BlockNumber leftsib;
	BlockNumber rightsib;
	Buffer		buffer;
	Page		page;
	BTPageOpaque pageop;

	leftsib = xlrec->leftsib;
	rightsib = xlrec->rightsib;

	/*
	 * In normal operation, we would lock all the pages this WAL record
	 * touches before changing any of them.  In WAL replay, it should be okay
	 * to lock just one page at a time, since no concurrent index updates can
	 * be happening, and readers should not care whether they arrive at the
	 * target page or not (since it's surely empty).
	 */

	/* Fix left-link of right sibling */
	if (XLogReadBufferForRedo(record, 2, &buffer) == BLK_NEEDS_REDO)
	{
		page = (Page) BufferGetPage(buffer);
		pageop = (BTPageOpaque) PageGetSpecialPointer(page);
		pageop->btpo_prev = leftsib;

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* Fix right-link of left sibling, if any */
	if (leftsib != P_NONE)
	{
		if (XLogReadBufferForRedo(record, 1, &buffer) == BLK_NEEDS_REDO)
		{
			page = (Page) BufferGetPage(buffer);
			pageop = (BTPageOpaque) PageGetSpecialPointer(page);
			pageop->btpo_next = rightsib;

			PageSetLSN(page, lsn);
			MarkBufferDirty(buffer);
		}
		if (BufferIsValid(buffer))
			UnlockReleaseBuffer(buffer);
	}

	/* Rewrite target page as empty deleted page */
	buffer = XLogInitBufferForRedo(record, 0);
	page = (Page) BufferGetPage(buffer);

	_bt_pageinit(page, BufferGetPageSize(buffer));
	pageop = (BTPageOpaque) PageGetSpecialPointer(page);

	pageop->btpo_prev = leftsib;
	pageop->btpo_next = rightsib;
	pageop->btpo.xact = xlrec->btpo_xact;
	pageop->btpo_flags = BTP_DELETED;
	pageop->btpo_cycleid = 0;

	PageSetLSN(page, lsn);
	MarkBufferDirty(buffer);
	UnlockReleaseBuffer(buffer);

	/*
	 * If we deleted a parent of the targeted leaf page, instead of the leaf
	 * itself, update the leaf to point to the next remaining child in the
	 * branch.
	 */
	if (XLogRecHasBlockRef(record, 3))
	{
		/*
		 * There is no real data on the page, so we just re-create it from
		 * scratch using the information from the WAL record.
		 */
		IndexTupleData trunctuple;

		buffer = XLogInitBufferForRedo(record, 3);
		page = (Page) BufferGetPage(buffer);

		_bt_pageinit(page, BufferGetPageSize(buffer));
		pageop = (BTPageOpaque) PageGetSpecialPointer(page);

		pageop->btpo_flags = BTP_HALF_DEAD | BTP_LEAF;
		pageop->btpo_prev = xlrec->leafleftsib;
		pageop->btpo_next = xlrec->leafrightsib;
		pageop->btpo.level = 0;
		pageop->btpo_cycleid = 0;

		/* Add a dummy hikey item */
		MemSet(&trunctuple, 0, sizeof(IndexTupleData));
		trunctuple.t_info = sizeof(IndexTupleData);
		BTreeTupleSetTopParent(&trunctuple, xlrec->topparent);

		if (PageAddItem(page, (Item) &trunctuple, sizeof(IndexTupleData), P_HIKEY,
						false, false) == InvalidOffsetNumber)
			elog(ERROR, "could not add dummy high key to half-dead page");

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
		UnlockReleaseBuffer(buffer);
	}

	/* Update metapage if needed */
	if (info == XLOG_BTREE_UNLINK_PAGE_META)
		_bt_restore_meta(record, 4);
}