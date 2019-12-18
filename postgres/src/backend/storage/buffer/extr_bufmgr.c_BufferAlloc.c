#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_22__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  buf_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  relNode; int /*<<< orphan*/  dbNode; int /*<<< orphan*/  spcNode; } ;
struct TYPE_20__ {TYPE_12__ node; } ;
struct TYPE_21__ {TYPE_1__ smgr_rnode; } ;
typedef  TYPE_2__* SMgrRelation ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  ForkNumber ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  TYPE_3__ BufferDesc ;
typedef  int /*<<< orphan*/ * BufferAccessStrategy ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_CHECKPOINT_NEEDED ; 
 int BM_DIRTY ; 
 int BM_IO_ERROR ; 
 int BM_JUST_DIRTIED ; 
 int BM_PERMANENT ; 
 int BM_TAG_VALID ; 
 int BM_VALID ; 
 int BUF_FLAG_MASK ; 
 int BUF_STATE_GET_REFCOUNT (int) ; 
 int BUF_USAGECOUNT_MASK ; 
 int BUF_USAGECOUNT_ONE ; 
 int /*<<< orphan*/  BackendWritebackContext ; 
 int /*<<< orphan*/ * BufMappingPartitionLock (int) ; 
 int /*<<< orphan*/  BufTableDelete (int /*<<< orphan*/ *,int) ; 
 int BufTableHashCode (int /*<<< orphan*/ *) ; 
 int BufTableInsert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int BufTableLookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BufferDescriptorGetContentLock (TYPE_3__*) ; 
 int /*<<< orphan*/  BufferGetLSN (TYPE_3__*) ; 
 int /*<<< orphan*/  FlushBuffer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* GetBufferDescriptor (int) ; 
 int /*<<< orphan*/  INIT_BUFFERTAG (int /*<<< orphan*/ ,TYPE_12__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_FORKNUM ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LWLockConditionalAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int LockBufHdr (TYPE_3__*) ; 
 int PinBuffer (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PinBuffer_Locked (TYPE_3__*) ; 
 char RELPERSISTENCE_PERMANENT ; 
 int /*<<< orphan*/  ReservePrivateRefCountEntry () ; 
 int /*<<< orphan*/  ScheduleBufferTagForWriteback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ StartBufferIO (TYPE_3__*,int) ; 
 TYPE_3__* StrategyGetBuffer (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ StrategyRejectBuffer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_BUFFER_WRITE_DIRTY_DONE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_BUFFER_WRITE_DIRTY_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  UnpinBuffer (TYPE_3__*,int) ; 
 scalar_t__ XLogNeedsFlush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BufferDesc *
BufferAlloc(SMgrRelation smgr, char relpersistence, ForkNumber forkNum,
			BlockNumber blockNum,
			BufferAccessStrategy strategy,
			bool *foundPtr)
{
	BufferTag	newTag;			/* identity of requested block */
	uint32		newHash;		/* hash value for newTag */
	LWLock	   *newPartitionLock;	/* buffer partition lock for it */
	BufferTag	oldTag;			/* previous identity of selected buffer */
	uint32		oldHash;		/* hash value for oldTag */
	LWLock	   *oldPartitionLock;	/* buffer partition lock for it */
	uint32		oldFlags;
	int			buf_id;
	BufferDesc *buf;
	bool		valid;
	uint32		buf_state;

	/* create a tag so we can lookup the buffer */
	INIT_BUFFERTAG(newTag, smgr->smgr_rnode.node, forkNum, blockNum);

	/* determine its hash code and partition lock ID */
	newHash = BufTableHashCode(&newTag);
	newPartitionLock = BufMappingPartitionLock(newHash);

	/* see if the block is in the buffer pool already */
	LWLockAcquire(newPartitionLock, LW_SHARED);
	buf_id = BufTableLookup(&newTag, newHash);
	if (buf_id >= 0)
	{
		/*
		 * Found it.  Now, pin the buffer so no one can steal it from the
		 * buffer pool, and check to see if the correct data has been loaded
		 * into the buffer.
		 */
		buf = GetBufferDescriptor(buf_id);

		valid = PinBuffer(buf, strategy);

		/* Can release the mapping lock as soon as we've pinned it */
		LWLockRelease(newPartitionLock);

		*foundPtr = true;

		if (!valid)
		{
			/*
			 * We can only get here if (a) someone else is still reading in
			 * the page, or (b) a previous read attempt failed.  We have to
			 * wait for any active read attempt to finish, and then set up our
			 * own read attempt if the page is still not BM_VALID.
			 * StartBufferIO does it all.
			 */
			if (StartBufferIO(buf, true))
			{
				/*
				 * If we get here, previous attempts to read the buffer must
				 * have failed ... but we shall bravely try again.
				 */
				*foundPtr = false;
			}
		}

		return buf;
	}

	/*
	 * Didn't find it in the buffer pool.  We'll have to initialize a new
	 * buffer.  Remember to unlock the mapping lock while doing the work.
	 */
	LWLockRelease(newPartitionLock);

	/* Loop here in case we have to try another victim buffer */
	for (;;)
	{
		/*
		 * Ensure, while the spinlock's not yet held, that there's a free
		 * refcount entry.
		 */
		ReservePrivateRefCountEntry();

		/*
		 * Select a victim buffer.  The buffer is returned with its header
		 * spinlock still held!
		 */
		buf = StrategyGetBuffer(strategy, &buf_state);

		Assert(BUF_STATE_GET_REFCOUNT(buf_state) == 0);

		/* Must copy buffer flags while we still hold the spinlock */
		oldFlags = buf_state & BUF_FLAG_MASK;

		/* Pin the buffer and then release the buffer spinlock */
		PinBuffer_Locked(buf);

		/*
		 * If the buffer was dirty, try to write it out.  There is a race
		 * condition here, in that someone might dirty it after we released it
		 * above, or even while we are writing it out (since our share-lock
		 * won't prevent hint-bit updates).  We will recheck the dirty bit
		 * after re-locking the buffer header.
		 */
		if (oldFlags & BM_DIRTY)
		{
			/*
			 * We need a share-lock on the buffer contents to write it out
			 * (else we might write invalid data, eg because someone else is
			 * compacting the page contents while we write).  We must use a
			 * conditional lock acquisition here to avoid deadlock.  Even
			 * though the buffer was not pinned (and therefore surely not
			 * locked) when StrategyGetBuffer returned it, someone else could
			 * have pinned and exclusive-locked it by the time we get here. If
			 * we try to get the lock unconditionally, we'd block waiting for
			 * them; if they later block waiting for us, deadlock ensues.
			 * (This has been observed to happen when two backends are both
			 * trying to split btree index pages, and the second one just
			 * happens to be trying to split the page the first one got from
			 * StrategyGetBuffer.)
			 */
			if (LWLockConditionalAcquire(BufferDescriptorGetContentLock(buf),
										 LW_SHARED))
			{
				/*
				 * If using a nondefault strategy, and writing the buffer
				 * would require a WAL flush, let the strategy decide whether
				 * to go ahead and write/reuse the buffer or to choose another
				 * victim.  We need lock to inspect the page LSN, so this
				 * can't be done inside StrategyGetBuffer.
				 */
				if (strategy != NULL)
				{
					XLogRecPtr	lsn;

					/* Read the LSN while holding buffer header lock */
					buf_state = LockBufHdr(buf);
					lsn = BufferGetLSN(buf);
					UnlockBufHdr(buf, buf_state);

					if (XLogNeedsFlush(lsn) &&
						StrategyRejectBuffer(strategy, buf))
					{
						/* Drop lock/pin and loop around for another buffer */
						LWLockRelease(BufferDescriptorGetContentLock(buf));
						UnpinBuffer(buf, true);
						continue;
					}
				}

				/* OK, do the I/O */
				TRACE_POSTGRESQL_BUFFER_WRITE_DIRTY_START(forkNum, blockNum,
														  smgr->smgr_rnode.node.spcNode,
														  smgr->smgr_rnode.node.dbNode,
														  smgr->smgr_rnode.node.relNode);

				FlushBuffer(buf, NULL);
				LWLockRelease(BufferDescriptorGetContentLock(buf));

				ScheduleBufferTagForWriteback(&BackendWritebackContext,
											  &buf->tag);

				TRACE_POSTGRESQL_BUFFER_WRITE_DIRTY_DONE(forkNum, blockNum,
														 smgr->smgr_rnode.node.spcNode,
														 smgr->smgr_rnode.node.dbNode,
														 smgr->smgr_rnode.node.relNode);
			}
			else
			{
				/*
				 * Someone else has locked the buffer, so give it up and loop
				 * back to get another one.
				 */
				UnpinBuffer(buf, true);
				continue;
			}
		}

		/*
		 * To change the association of a valid buffer, we'll need to have
		 * exclusive lock on both the old and new mapping partitions.
		 */
		if (oldFlags & BM_TAG_VALID)
		{
			/*
			 * Need to compute the old tag's hashcode and partition lock ID.
			 * XXX is it worth storing the hashcode in BufferDesc so we need
			 * not recompute it here?  Probably not.
			 */
			oldTag = buf->tag;
			oldHash = BufTableHashCode(&oldTag);
			oldPartitionLock = BufMappingPartitionLock(oldHash);

			/*
			 * Must lock the lower-numbered partition first to avoid
			 * deadlocks.
			 */
			if (oldPartitionLock < newPartitionLock)
			{
				LWLockAcquire(oldPartitionLock, LW_EXCLUSIVE);
				LWLockAcquire(newPartitionLock, LW_EXCLUSIVE);
			}
			else if (oldPartitionLock > newPartitionLock)
			{
				LWLockAcquire(newPartitionLock, LW_EXCLUSIVE);
				LWLockAcquire(oldPartitionLock, LW_EXCLUSIVE);
			}
			else
			{
				/* only one partition, only one lock */
				LWLockAcquire(newPartitionLock, LW_EXCLUSIVE);
			}
		}
		else
		{
			/* if it wasn't valid, we need only the new partition */
			LWLockAcquire(newPartitionLock, LW_EXCLUSIVE);
			/* remember we have no old-partition lock or tag */
			oldPartitionLock = NULL;
			/* keep the compiler quiet about uninitialized variables */
			oldHash = 0;
		}

		/*
		 * Try to make a hashtable entry for the buffer under its new tag.
		 * This could fail because while we were writing someone else
		 * allocated another buffer for the same block we want to read in.
		 * Note that we have not yet removed the hashtable entry for the old
		 * tag.
		 */
		buf_id = BufTableInsert(&newTag, newHash, buf->buf_id);

		if (buf_id >= 0)
		{
			/*
			 * Got a collision. Someone has already done what we were about to
			 * do. We'll just handle this as if it were found in the buffer
			 * pool in the first place.  First, give up the buffer we were
			 * planning to use.
			 */
			UnpinBuffer(buf, true);

			/* Can give up that buffer's mapping partition lock now */
			if (oldPartitionLock != NULL &&
				oldPartitionLock != newPartitionLock)
				LWLockRelease(oldPartitionLock);

			/* remaining code should match code at top of routine */

			buf = GetBufferDescriptor(buf_id);

			valid = PinBuffer(buf, strategy);

			/* Can release the mapping lock as soon as we've pinned it */
			LWLockRelease(newPartitionLock);

			*foundPtr = true;

			if (!valid)
			{
				/*
				 * We can only get here if (a) someone else is still reading
				 * in the page, or (b) a previous read attempt failed.  We
				 * have to wait for any active read attempt to finish, and
				 * then set up our own read attempt if the page is still not
				 * BM_VALID.  StartBufferIO does it all.
				 */
				if (StartBufferIO(buf, true))
				{
					/*
					 * If we get here, previous attempts to read the buffer
					 * must have failed ... but we shall bravely try again.
					 */
					*foundPtr = false;
				}
			}

			return buf;
		}

		/*
		 * Need to lock the buffer header too in order to change its tag.
		 */
		buf_state = LockBufHdr(buf);

		/*
		 * Somebody could have pinned or re-dirtied the buffer while we were
		 * doing the I/O and making the new hashtable entry.  If so, we can't
		 * recycle this buffer; we must undo everything we've done and start
		 * over with a new victim buffer.
		 */
		oldFlags = buf_state & BUF_FLAG_MASK;
		if (BUF_STATE_GET_REFCOUNT(buf_state) == 1 && !(oldFlags & BM_DIRTY))
			break;

		UnlockBufHdr(buf, buf_state);
		BufTableDelete(&newTag, newHash);
		if (oldPartitionLock != NULL &&
			oldPartitionLock != newPartitionLock)
			LWLockRelease(oldPartitionLock);
		LWLockRelease(newPartitionLock);
		UnpinBuffer(buf, true);
	}

	/*
	 * Okay, it's finally safe to rename the buffer.
	 *
	 * Clearing BM_VALID here is necessary, clearing the dirtybits is just
	 * paranoia.  We also reset the usage_count since any recency of use of
	 * the old content is no longer relevant.  (The usage_count starts out at
	 * 1 so that the buffer can survive one clock-sweep pass.)
	 *
	 * Make sure BM_PERMANENT is set for buffers that must be written at every
	 * checkpoint.  Unlogged buffers only need to be written at shutdown
	 * checkpoints, except for their "init" forks, which need to be treated
	 * just like permanent relations.
	 */
	buf->tag = newTag;
	buf_state &= ~(BM_VALID | BM_DIRTY | BM_JUST_DIRTIED |
				   BM_CHECKPOINT_NEEDED | BM_IO_ERROR | BM_PERMANENT |
				   BUF_USAGECOUNT_MASK);
	if (relpersistence == RELPERSISTENCE_PERMANENT || forkNum == INIT_FORKNUM)
		buf_state |= BM_TAG_VALID | BM_PERMANENT | BUF_USAGECOUNT_ONE;
	else
		buf_state |= BM_TAG_VALID | BUF_USAGECOUNT_ONE;

	UnlockBufHdr(buf, buf_state);

	if (oldPartitionLock != NULL)
	{
		BufTableDelete(&oldTag, oldHash);
		if (oldPartitionLock != newPartitionLock)
			LWLockRelease(oldPartitionLock);
	}

	LWLockRelease(newPartitionLock);

	/*
	 * Buffer contents are currently invalid.  Try to get the io_in_progress
	 * lock.  If StartBufferIO returns false, then someone else managed to
	 * read it before we did, so there's nothing left for BufferAlloc() to do.
	 */
	if (StartBufferIO(buf, true))
		*foundPtr = false;
	else
		*foundPtr = true;

	return buf;
}