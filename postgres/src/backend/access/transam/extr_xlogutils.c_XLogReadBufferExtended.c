#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SMgrRelation ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  scalar_t__ ReadBufferMode ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int InRecovery ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 scalar_t__ RBM_NORMAL ; 
 scalar_t__ RBM_NORMAL_NO_LOG ; 
 scalar_t__ RBM_ZERO_AND_CLEANUP_LOCK ; 
 scalar_t__ RBM_ZERO_AND_LOCK ; 
 scalar_t__ ReadBufferWithoutRelcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  log_invalid_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  smgrcreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smgrnblocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgropen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Buffer
XLogReadBufferExtended(RelFileNode rnode, ForkNumber forknum,
					   BlockNumber blkno, ReadBufferMode mode)
{
	BlockNumber lastblock;
	Buffer		buffer;
	SMgrRelation smgr;

	Assert(blkno != P_NEW);

	/* Open the relation at smgr level */
	smgr = smgropen(rnode, InvalidBackendId);

	/*
	 * Create the target file if it doesn't already exist.  This lets us cope
	 * if the replay sequence contains writes to a relation that is later
	 * deleted.  (The original coding of this routine would instead suppress
	 * the writes, but that seems like it risks losing valuable data if the
	 * filesystem loses an inode during a crash.  Better to write the data
	 * until we are actually told to delete the file.)
	 */
	smgrcreate(smgr, forknum, true);

	lastblock = smgrnblocks(smgr, forknum);

	if (blkno < lastblock)
	{
		/* page exists in file */
		buffer = ReadBufferWithoutRelcache(rnode, forknum, blkno,
										   mode, NULL);
	}
	else
	{
		/* hm, page doesn't exist in file */
		if (mode == RBM_NORMAL)
		{
			log_invalid_page(rnode, forknum, blkno, false);
			return InvalidBuffer;
		}
		if (mode == RBM_NORMAL_NO_LOG)
			return InvalidBuffer;
		/* OK to extend the file */
		/* we do this in recovery only - no rel-extension lock needed */
		Assert(InRecovery);
		buffer = InvalidBuffer;
		do
		{
			if (buffer != InvalidBuffer)
			{
				if (mode == RBM_ZERO_AND_LOCK || mode == RBM_ZERO_AND_CLEANUP_LOCK)
					LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
				ReleaseBuffer(buffer);
			}
			buffer = ReadBufferWithoutRelcache(rnode, forknum,
											   P_NEW, mode, NULL);
		}
		while (BufferGetBlockNumber(buffer) < blkno);
		/* Handle the corner case that P_NEW returns non-consecutive pages */
		if (BufferGetBlockNumber(buffer) != blkno)
		{
			if (mode == RBM_ZERO_AND_LOCK || mode == RBM_ZERO_AND_CLEANUP_LOCK)
				LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
			ReleaseBuffer(buffer);
			buffer = ReadBufferWithoutRelcache(rnode, forknum, blkno,
											   mode, NULL);
		}
	}

	if (mode == RBM_NORMAL)
	{
		/* check that page has been initialized */
		Page		page = (Page) BufferGetPage(buffer);

		/*
		 * We assume that PageIsNew is safe without a lock. During recovery,
		 * there should be no other backends that could modify the buffer at
		 * the same time.
		 */
		if (PageIsNew(page))
		{
			ReleaseBuffer(buffer);
			log_invalid_page(rnode, forknum, blkno, true);
			return InvalidBuffer;
		}
	}

	return buffer;
}