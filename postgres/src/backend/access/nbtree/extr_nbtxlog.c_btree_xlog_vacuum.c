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
struct TYPE_9__ {scalar_t__ lastBlockVacuumed; } ;
typedef  TYPE_1__ xl_btree_vacuum ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  EndRecPtr; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_11__ {int /*<<< orphan*/  btpo_flags; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 scalar_t__ BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BTP_HAS_GARBAGE ; 
 scalar_t__ BlockNumberIsValid (scalar_t__) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ HotStandbyActiveInReplay () ; 
 int /*<<< orphan*/  LockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageIndexMultiDelete (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  RBM_NORMAL_NO_LOG ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogReadBufferForRedoExtended (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 char* XLogRecGetBlockData (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ XLogRecGetData (TYPE_2__*) ; 

__attribute__((used)) static void
btree_xlog_vacuum(XLogReaderState *record)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	Buffer		buffer;
	Page		page;
	BTPageOpaque opaque;
#ifdef UNUSED
	xl_btree_vacuum *xlrec = (xl_btree_vacuum *) XLogRecGetData(record);

	/*
	 * This section of code is thought to be no longer needed, after analysis
	 * of the calling paths. It is retained to allow the code to be reinstated
	 * if a flaw is revealed in that thinking.
	 *
	 * If we are running non-MVCC scans using this index we need to do some
	 * additional work to ensure correctness, which is known as a "pin scan"
	 * described in more detail in next paragraphs. We used to do the extra
	 * work in all cases, whereas we now avoid that work in most cases. If
	 * lastBlockVacuumed is set to InvalidBlockNumber then we skip the
	 * additional work required for the pin scan.
	 *
	 * Avoiding this extra work is important since it requires us to touch
	 * every page in the index, so is an O(N) operation. Worse, it is an
	 * operation performed in the foreground during redo, so it delays
	 * replication directly.
	 *
	 * If queries might be active then we need to ensure every leaf page is
	 * unpinned between the lastBlockVacuumed and the current block, if there
	 * are any.  This prevents replay of the VACUUM from reaching the stage of
	 * removing heap tuples while there could still be indexscans "in flight"
	 * to those particular tuples for those scans which could be confused by
	 * finding new tuples at the old TID locations (see nbtree/README).
	 *
	 * It might be worth checking if there are actually any backends running;
	 * if not, we could just skip this.
	 *
	 * Since VACUUM can visit leaf pages out-of-order, it might issue records
	 * with lastBlockVacuumed >= block; that's not an error, it just means
	 * nothing to do now.
	 *
	 * Note: since we touch all pages in the range, we will lock non-leaf
	 * pages, and also any empty (all-zero) pages that may be in the index. It
	 * doesn't seem worth the complexity to avoid that.  But it's important
	 * that HotStandbyActiveInReplay() will not return true if the database
	 * isn't yet consistent; so we need not fear reading still-corrupt blocks
	 * here during crash recovery.
	 */
	if (HotStandbyActiveInReplay() && BlockNumberIsValid(xlrec->lastBlockVacuumed))
	{
		RelFileNode thisrnode;
		BlockNumber thisblkno;
		BlockNumber blkno;

		XLogRecGetBlockTag(record, 0, &thisrnode, NULL, &thisblkno);

		for (blkno = xlrec->lastBlockVacuumed + 1; blkno < thisblkno; blkno++)
		{
			/*
			 * We use RBM_NORMAL_NO_LOG mode because it's not an error
			 * condition to see all-zero pages.  The original btvacuumpage
			 * scan would have skipped over all-zero pages, noting them in FSM
			 * but not bothering to initialize them just yet; so we mustn't
			 * throw an error here.  (We could skip acquiring the cleanup lock
			 * if PageIsNew, but it's probably not worth the cycles to test.)
			 *
			 * XXX we don't actually need to read the block, we just need to
			 * confirm it is unpinned. If we had a special call into the
			 * buffer manager we could optimise this so that if the block is
			 * not in shared_buffers we confirm it as unpinned. Optimizing
			 * this is now moot, since in most cases we avoid the scan.
			 */
			buffer = XLogReadBufferExtended(thisrnode, MAIN_FORKNUM, blkno,
											RBM_NORMAL_NO_LOG);
			if (BufferIsValid(buffer))
			{
				LockBufferForCleanup(buffer);
				UnlockReleaseBuffer(buffer);
			}
		}
	}
#endif

	/*
	 * Like in btvacuumpage(), we need to take a cleanup lock on every leaf
	 * page. See nbtree/README for details.
	 */
	if (XLogReadBufferForRedoExtended(record, 0, RBM_NORMAL, true, &buffer)
		== BLK_NEEDS_REDO)
	{
		char	   *ptr;
		Size		len;

		ptr = XLogRecGetBlockData(record, 0, &len);

		page = (Page) BufferGetPage(buffer);

		if (len > 0)
		{
			OffsetNumber *unused;
			OffsetNumber *unend;

			unused = (OffsetNumber *) ptr;
			unend = (OffsetNumber *) ((char *) ptr + len);

			if ((unend - unused) > 0)
				PageIndexMultiDelete(page, unused, unend - unused);
		}

		/*
		 * Mark the page as not containing any LP_DEAD items --- see comments
		 * in _bt_delitems_vacuum().
		 */
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		opaque->btpo_flags &= ~BTP_HAS_GARBAGE;

		PageSetLSN(page, lsn);
		MarkBufferDirty(buffer);
	}
	if (BufferIsValid(buffer))
		UnlockReleaseBuffer(buffer);
}