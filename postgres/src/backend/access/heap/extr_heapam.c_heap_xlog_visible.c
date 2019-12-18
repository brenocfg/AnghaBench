#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  cutoff_xid; } ;
typedef  TYPE_1__ xl_heap_visible ;
typedef  scalar_t__ XLogRedoAction ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_9__ {scalar_t__ EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 scalar_t__ BLK_NEEDS_REDO ; 
 scalar_t__ BLK_RESTORED ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFakeRelcacheEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeFakeRelcacheEntry (int /*<<< orphan*/ ) ; 
 scalar_t__ InHotStandby ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetAllVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_ZERO_ON_ERROR ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int VISIBILITYMAP_VALID_BITS ; 
 scalar_t__ XLogReadBufferForRedo (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogReadBufferForRedoExtended (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 
 int /*<<< orphan*/  XLogRecordPageWithFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visibilitymap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
heap_xlog_visible(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	xl_heap_visible *xlrec = (xl_heap_visible *) XLogRecGetData(record);
	Buffer		vmbuffer = InvalidBuffer;
	Buffer		buffer;
	Page		page;
	RelFileNode rnode;
	BlockNumber blkno;
	XLogRedoAction action;

	XLogRecGetBlockTag(record, 1, &rnode, NULL, &blkno);

	/*
	 * If there are any Hot Standby transactions running that have an xmin
	 * horizon old enough that this page isn't all-visible for them, they
	 * might incorrectly decide that an index-only scan can skip a heap fetch.
	 *
	 * NB: It might be better to throw some kind of "soft" conflict here that
	 * forces any index-only scan that is in flight to perform heap fetches,
	 * rather than killing the transaction outright.
	 */
	if (InHotStandby)
		ResolveRecoveryConflictWithSnapshot(xlrec->cutoff_xid, rnode);

	/*
	 * Read the heap page, if it still exists. If the heap file has dropped or
	 * truncated later in recovery, we don't need to update the page, but we'd
	 * better still update the visibility map.
	 */
	action = XLogReadBufferForRedo(record, 1, &buffer);
	if (action == BLK_NEEDS_REDO)
	{
		/*
		 * We don't bump the LSN of the heap page when setting the visibility
		 * map bit (unless checksums or wal_hint_bits is enabled, in which
		 * case we must), because that would generate an unworkable volume of
		 * full-page writes.  This exposes us to torn page hazards, but since
		 * we're not inspecting the existing page contents in any way, we
		 * don't care.
		 *
		 * However, all operations that clear the visibility map bit *do* bump
		 * the LSN, and those operations will only be replayed if the XLOG LSN
		 * follows the page LSN.  Thus, if the page LSN has advanced past our
		 * XLOG record's LSN, we mustn't mark the page all-visible, because
		 * the subsequent update won't be replayed to clear the flag.
		 */
		page = BufferGetPage(buffer);

		PageSetAllVisible(page);

		MarkBufferDirty(buffer);
	}
	else if (action == BLK_RESTORED)
	{
		/*
		 * If heap block was backed up, we already restored it and there's
		 * nothing more to do. (This can only happen with checksums or
		 * wal_log_hints enabled.)
		 */
	}

	if (BufferIsValid(buffer))
	{
		Size		space = PageGetFreeSpace(BufferGetPage(buffer));

		UnlockReleaseBuffer(buffer);

		/*
		 * Since FSM is not WAL-logged and only updated heuristically, it
		 * easily becomes stale in standbys.  If the standby is later promoted
		 * and runs VACUUM, it will skip updating individual free space
		 * figures for pages that became all-visible (or all-frozen, depending
		 * on the vacuum mode,) which is troublesome when FreeSpaceMapVacuum
		 * propagates too optimistic free space values to upper FSM layers;
		 * later inserters try to use such pages only to find out that they
		 * are unusable.  This can cause long stalls when there are many such
		 * pages.
		 *
		 * Forestall those problems by updating FSM's idea about a page that
		 * is becoming all-visible or all-frozen.
		 *
		 * Do this regardless of a full-page image being applied, since the
		 * FSM data is not in the page anyway.
		 */
		if (xlrec->flags & VISIBILITYMAP_VALID_BITS)
			XLogRecordPageWithFreeSpace(rnode, blkno, space);
	}

	/*
	 * Even if we skipped the heap page update due to the LSN interlock, it's
	 * still safe to update the visibility map.  Any WAL record that clears
	 * the visibility map bit does so before checking the page LSN, so any
	 * bits that need to be cleared will still be cleared.
	 */
	if (XLogReadBufferForRedoExtended(record, 0, RBM_ZERO_ON_ERROR, false,
									  &vmbuffer) == BLK_NEEDS_REDO)
	{
		Page		vmpage = BufferGetPage(vmbuffer);
		Relation	reln;

		/* initialize the page if it was read as zeros */
		if (PageIsNew(vmpage))
			PageInit(vmpage, BLCKSZ, 0);

		/*
		 * XLogReadBufferForRedoExtended locked the buffer. But
		 * visibilitymap_set will handle locking itself.
		 */
		LockBuffer(vmbuffer, BUFFER_LOCK_UNLOCK);

		reln = CreateFakeRelcacheEntry(rnode);
		visibilitymap_pin(reln, blkno, &vmbuffer);

		/*
		 * Don't set the bit if replay has already passed this point.
		 *
		 * It might be safe to do this unconditionally; if replay has passed
		 * this point, we'll replay at least as far this time as we did
		 * before, and if this bit needs to be cleared, the record responsible
		 * for doing so should be again replayed, and clear it.  For right
		 * now, out of an abundance of conservatism, we use the same test here
		 * we did for the heap page.  If this results in a dropped bit, no
		 * real harm is done; and the next VACUUM will fix it.
		 */
		if (lsn > PageGetLSN(vmpage))
			visibilitymap_set(reln, blkno, InvalidBuffer, lsn, vmbuffer,
							  xlrec->cutoff_xid, xlrec->flags);

		ReleaseBuffer(vmbuffer);
		FreeFakeRelcacheEntry(reln);
	}
	else if (BufferIsValid(vmbuffer))
		UnlockReleaseBuffer(vmbuffer);
}