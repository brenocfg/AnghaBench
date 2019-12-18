#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int /*<<< orphan*/  locking_xid; int /*<<< orphan*/  infobits_set; int /*<<< orphan*/  offnum; } ;
typedef  TYPE_1__ xl_heap_lock ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_12__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_13__ {int t_infomask; int /*<<< orphan*/  t_ctid; int /*<<< orphan*/  t_infomask2; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/ * ItemId ;
typedef  TYPE_3__* HeapTupleHeader ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFakeRelcacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FirstCommandId ; 
 int /*<<< orphan*/  FreeFakeRelcacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_KEYS_UPDATED ; 
 int HEAP_MOVED ; 
 int HEAP_XMAX_BITS ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int /*<<< orphan*/  HeapTupleHeaderClearHotUpdated (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetCmax (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapTupleHeaderSetXmax (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemIdIsNormal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PageGetItemId (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VISIBILITYMAP_ALL_FROZEN ; 
 int XLH_LOCK_ALL_FROZEN_CLEARED ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fix_infomask_from_infobits (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visibilitymap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
heap_xlog_lock(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_heap_lock *xlrec = (xl_heap_lock *) XLogRecGetData(record);
	Buffer		buffer;
	Page		page;
	OffsetNumber offnum;
	ItemId		lp = NULL;
	HeapTupleHeader htup;

	/*
	 * The visibility map may need to be fixed even if the heap page is
	 * already up-to-date.
	 */
	if (xlrec->flags & XLH_LOCK_ALL_FROZEN_CLEARED)
	{
		RelFileNode rnode;
		Buffer		vmbuffer = InvalidBuffer;
		BlockNumber block;
		Relation	reln;

		XLogRecGetBlockTag(record, 0, &rnode, NULL, &block);
		reln = CreateFakeRelcacheEntry(rnode);

		visibilitymap_pin(reln, block, &vmbuffer);
		visibilitymap_clear(reln, block, vmbuffer, VISIBILITYMAP_ALL_FROZEN);

		ReleaseBuffer(vmbuffer);
		FreeFakeRelcacheEntry(reln);
	}

	if (XLogReadBufferForRedo(record, 0, &buffer) == BLK_NEEDS_REDO)
	{
		page = (Page) BufferGetPage(buffer);

		offnum = xlrec->offnum;
		if (PageGetMaxOffsetNumber(page) >= offnum)
			lp = PageGetItemId(page, offnum);

		if (PageGetMaxOffsetNumber(page) < offnum || !ItemIdIsNormal(lp))
			elog(PANIC, "invalid lp");

		htup = (HeapTupleHeader) PageGetItem(page, lp);

		htup->t_infomask &= ~(HEAP_XMAX_BITS | HEAP_MOVED);
		htup->t_infomask2 &= ~HEAP_KEYS_UPDATED;
		fix_infomask_from_infobits(xlrec->infobits_set, &htup->t_infomask,
								   &htup->t_infomask2);

		/*
		 * Clear relevant update flags, but only if the modified infomask says
		 * there's no update.
		 */
		if (HEAP_XMAX_IS_LOCKED_ONLY(htup->t_infomask))
		{
			HeapTupleHeaderClearHotUpdated(htup);
			/* Make sure there is no forward chain link in t_ctid */
			ItemPointerSet(&htup->t_ctid,
						   BufferGetBlockNumber(buffer),
						   offnum);
		}
		HeapTupleHeaderSetXmax(htup, xlrec->locking_xid);
		HeapTupleHeaderSetCmax(htup, FirstCommandId, false);
		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}