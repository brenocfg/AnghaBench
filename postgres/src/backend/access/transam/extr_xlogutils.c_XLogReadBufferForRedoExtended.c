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
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  XLogRedoAction ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_9__ {scalar_t__ EndRecPtr; TYPE_1__* blocks; } ;
typedef  TYPE_2__ XLogReaderState ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  int /*<<< orphan*/  ReadBufferMode ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ ForkNumber ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int BKPBLOCK_WILL_INIT ; 
 int /*<<< orphan*/  BLK_DONE ; 
 int /*<<< orphan*/  BLK_NEEDS_REDO ; 
 int /*<<< orphan*/  BLK_NOTFOUND ; 
 int /*<<< orphan*/  BLK_RESTORED ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FlushOneBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ INIT_FORKNUM ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBufferForCleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ PageGetLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RBM_ZERO_AND_CLEANUP_LOCK ; 
 int /*<<< orphan*/  RBM_ZERO_AND_LOCK ; 
 int /*<<< orphan*/  RestoreBlockImage (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogReadBufferExtended (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogRecBlockImageApply (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (TYPE_2__*,size_t,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasBlockImage (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

XLogRedoAction
XLogReadBufferForRedoExtended(XLogReaderState *record,
							  uint8 block_id,
							  ReadBufferMode mode, bool get_cleanup_lock,
							  Buffer *buf)
{
	XLogRecPtr	lsn = record->EndRecPtr;
	RelFileNode rnode;
	ForkNumber	forknum;
	BlockNumber blkno;
	Page		page;
	bool		zeromode;
	bool		willinit;

	if (!XLogRecGetBlockTag(record, block_id, &rnode, &forknum, &blkno))
	{
		/* Caller specified a bogus block_id */
		elog(PANIC, "failed to locate backup block with ID %d", block_id);
	}

	/*
	 * Make sure that if the block is marked with WILL_INIT, the caller is
	 * going to initialize it. And vice versa.
	 */
	zeromode = (mode == RBM_ZERO_AND_LOCK || mode == RBM_ZERO_AND_CLEANUP_LOCK);
	willinit = (record->blocks[block_id].flags & BKPBLOCK_WILL_INIT) != 0;
	if (willinit && !zeromode)
		elog(PANIC, "block with WILL_INIT flag in WAL record must be zeroed by redo routine");
	if (!willinit && zeromode)
		elog(PANIC, "block to be initialized in redo routine must be marked with WILL_INIT flag in the WAL record");

	/* If it has a full-page image and it should be restored, do it. */
	if (XLogRecBlockImageApply(record, block_id))
	{
		Assert(XLogRecHasBlockImage(record, block_id));
		*buf = XLogReadBufferExtended(rnode, forknum, blkno,
									  get_cleanup_lock ? RBM_ZERO_AND_CLEANUP_LOCK : RBM_ZERO_AND_LOCK);
		page = BufferGetPage(*buf);
		if (!RestoreBlockImage(record, block_id, page))
			elog(ERROR, "failed to restore block image");

		/*
		 * The page may be uninitialized. If so, we can't set the LSN because
		 * that would corrupt the page.
		 */
		if (!PageIsNew(page))
		{
			PageSetLSN(page, lsn);
		}

		MarkBufferDirty(*buf);

		/*
		 * At the end of crash recovery the init forks of unlogged relations
		 * are copied, without going through shared buffers. So we need to
		 * force the on-disk state of init forks to always be in sync with the
		 * state in shared buffers.
		 */
		if (forknum == INIT_FORKNUM)
			FlushOneBuffer(*buf);

		return BLK_RESTORED;
	}
	else
	{
		*buf = XLogReadBufferExtended(rnode, forknum, blkno, mode);
		if (BufferIsValid(*buf))
		{
			if (mode != RBM_ZERO_AND_LOCK && mode != RBM_ZERO_AND_CLEANUP_LOCK)
			{
				if (get_cleanup_lock)
					LockBufferForCleanup(*buf);
				else
					LockBuffer(*buf, BUFFER_LOCK_EXCLUSIVE);
			}
			if (lsn <= PageGetLSN(BufferGetPage(*buf)))
				return BLK_DONE;
			else
				return BLK_NEEDS_REDO;
		}
		else
			return BLK_NOTFOUND;
	}
}