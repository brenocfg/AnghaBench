#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  topparent; int /*<<< orphan*/  rightblk; int /*<<< orphan*/  leftblk; int /*<<< orphan*/  poffset; } ;
typedef  TYPE_2__ xl_btree_mark_page_halfdead ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_14__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_3__ XLogReaderState ;
struct TYPE_12__ {scalar_t__ level; } ;
struct TYPE_16__ {int btpo_flags; scalar_t__ btpo_cycleid; TYPE_1__ btpo; int /*<<< orphan*/  btpo_next; int /*<<< orphan*/  btpo_prev; } ;
struct TYPE_15__ {int t_info; } ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_4__ IndexTupleData ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_5__* BTPageOpaque ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int BTP_HALF_DEAD ; 
 int BTP_LEAF ; 
 int /*<<< orphan*/  BTreeInnerTupleGetDownLink (scalar_t__) ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTreeTupleSetTopParent (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_HIKEY ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogInitBufferForRedo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_3__*) ; 
 int /*<<< orphan*/  _bt_pageinit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
btree_xlog_mark_page_halfdead(uint8 info, XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_btree_mark_page_halfdead *xlrec = (xl_btree_mark_page_halfdead *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;
	BTPageOpaque pageop;
	IndexTupleData trunctuple;

	/*
	 * In normal operation, we would lock all the pages this WAL record
	 * touches before changing any of them.  In WAL replay, it should be okay
	 * to lock just one page at a time, since no concurrent index updates can
	 * be happening, and readers should not care whether they arrive at the
	 * target page or not (since it's surely empty).
	 */

	/* parent page */
	if (XLogReadBufferForRedo(record, 1, &buffer) == BLK_NEEDS_REDO)
	{
		OffsetNumber poffset;
		ItemId		itemid;
		IndexTuple	itup;
		OffsetNumber nextoffset;
		BlockNumber rightsib;

		page = (Page) BufferGetPage(buffer);
		pageop = (BTPageOpaque) PageGetSpecialPointer(page);

		poffset = xlrec->poffset;

		nextoffset = OffsetNumberNext(poffset);
		itemid = PageGetItemId(page, nextoffset);
		itup = (IndexTuple) PageGetItem(page, itemid);
		rightsib = BTreeInnerTupleGetDownLink(itup);

		itemid = PageGetItemId(page, poffset);
		itup = (IndexTuple) PageGetItem(page, itemid);
		BTreeInnerTupleSetDownLink(itup, rightsib);
		nextoffset = OffsetNumberNext(poffset);
		PageIndexTupleDelete(page, nextoffset);

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);

	/* Rewrite the leaf page as a halfdead page */
	buffer = XLogInitBufferForRedo(record, 0);
	page = (Page) BufferGetPage(buffer);

	_bt_pageinit(page, BufferGetPageSize(buffer));
	pageop = (BTPageOpaque) PageGetSpecialPointer(page);

	pageop->btpo_prev = xlrec->leftblk;
	pageop->btpo_next = xlrec->rightblk;
	pageop->btpo.level = 0;
	pageop->btpo_flags = BTP_HALF_DEAD | BTP_LEAF;
	pageop->btpo_cycleid = 0;

	/*
	 * Construct a dummy hikey item that points to the next parent to be
	 * deleted (if any).
	 */
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