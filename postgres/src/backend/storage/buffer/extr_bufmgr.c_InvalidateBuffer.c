#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_LOCKED ; 
 int BM_TAG_VALID ; 
 int /*<<< orphan*/  BUFFERTAGS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BUF_FLAG_MASK ; 
 scalar_t__ BUF_STATE_GET_REFCOUNT (int) ; 
 int BUF_USAGECOUNT_MASK ; 
 int /*<<< orphan*/ * BufMappingPartitionLock (int) ; 
 int /*<<< orphan*/  BufTableDelete (int /*<<< orphan*/ *,int) ; 
 int BufTableHashCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufferDescriptorGetBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  CLEAR_BUFFERTAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetPrivateRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int LockBufHdr (TYPE_1__*) ; 
 int /*<<< orphan*/  StrategyFreeBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  WaitIO (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
InvalidateBuffer(BufferDesc *buf)
{
	BufferTag	oldTag;
	uint32		oldHash;		/* hash value for oldTag */
	LWLock	   *oldPartitionLock;	/* buffer partition lock for it */
	uint32		oldFlags;
	uint32		buf_state;

	/* Save the original buffer tag before dropping the spinlock */
	oldTag = buf->tag;

	buf_state = pg_atomic_read_u32(&buf->state);
	Assert(buf_state & BM_LOCKED);
	UnlockBufHdr(buf, buf_state);

	/*
	 * Need to compute the old tag's hashcode and partition lock ID. XXX is it
	 * worth storing the hashcode in BufferDesc so we need not recompute it
	 * here?  Probably not.
	 */
	oldHash = BufTableHashCode(&oldTag);
	oldPartitionLock = BufMappingPartitionLock(oldHash);

retry:

	/*
	 * Acquire exclusive mapping lock in preparation for changing the buffer's
	 * association.
	 */
	LWLockAcquire(oldPartitionLock, LW_EXCLUSIVE);

	/* Re-lock the buffer header */
	buf_state = LockBufHdr(buf);

	/* If it's changed while we were waiting for lock, do nothing */
	if (!BUFFERTAGS_EQUAL(buf->tag, oldTag))
	{
		UnlockBufHdr(buf, buf_state);
		LWLockRelease(oldPartitionLock);
		return;
	}

	/*
	 * We assume the only reason for it to be pinned is that someone else is
	 * flushing the page out.  Wait for them to finish.  (This could be an
	 * infinite loop if the refcount is messed up... it would be nice to time
	 * out after awhile, but there seems no way to be sure how many loops may
	 * be needed.  Note that if the other guy has pinned the buffer but not
	 * yet done StartBufferIO, WaitIO will fall through and we'll effectively
	 * be busy-looping here.)
	 */
	if (BUF_STATE_GET_REFCOUNT(buf_state) != 0)
	{
		UnlockBufHdr(buf, buf_state);
		LWLockRelease(oldPartitionLock);
		/* safety check: should definitely not be our *own* pin */
		if (GetPrivateRefCount(BufferDescriptorGetBuffer(buf)) > 0)
			elog(ERROR, "buffer is pinned in InvalidateBuffer");
		WaitIO(buf);
		goto retry;
	}

	/*
	 * Clear out the buffer's tag and flags.  We must do this to ensure that
	 * linear scans of the buffer array don't think the buffer is valid.
	 */
	oldFlags = buf_state & BUF_FLAG_MASK;
	CLEAR_BUFFERTAG(buf->tag);
	buf_state &= ~(BUF_FLAG_MASK | BUF_USAGECOUNT_MASK);
	UnlockBufHdr(buf, buf_state);

	/*
	 * Remove the buffer from the lookup hashtable, if it was in there.
	 */
	if (oldFlags & BM_TAG_VALID)
		BufTableDelete(&oldTag, oldHash);

	/*
	 * Done with mapping lock.
	 */
	LWLockRelease(oldPartitionLock);

	/*
	 * Insert the buffer at the head of the list of free buffers.
	 */
	StrategyFreeBuffer(buf);
}