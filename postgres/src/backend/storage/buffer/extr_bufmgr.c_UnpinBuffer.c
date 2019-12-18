#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_13__ {int wait_backend_pid; int /*<<< orphan*/  state; } ;
struct TYPE_12__ {scalar_t__ refcount; } ;
typedef  TYPE_1__ PrivateRefCountEntry ;
typedef  TYPE_2__ BufferDesc ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_LOCKED ; 
 int BM_PIN_COUNT_WAITER ; 
 scalar_t__ BUF_REFCOUNT_ONE ; 
 int BUF_STATE_GET_REFCOUNT (int) ; 
 int /*<<< orphan*/  BufferDescriptorGetBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (TYPE_2__*) ; 
 int /*<<< orphan*/  BufferDescriptorGetIOLock (TYPE_2__*) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  ForgetPrivateRefCountEntry (TYPE_1__*) ; 
 TYPE_1__* GetPrivateRefCountEntry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int LockBufHdr (TYPE_2__*) ; 
 int /*<<< orphan*/  ProcSendSignal (int) ; 
 int /*<<< orphan*/  ResourceOwnerForgetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_2__*,int) ; 
 int WaitBufHdrUnlocked (TYPE_2__*) ; 
 scalar_t__ pg_atomic_compare_exchange_u32 (int /*<<< orphan*/ *,int*,int) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
UnpinBuffer(BufferDesc *buf, bool fixOwner)
{
	PrivateRefCountEntry *ref;
	Buffer		b = BufferDescriptorGetBuffer(buf);

	/* not moving as we're likely deleting it soon anyway */
	ref = GetPrivateRefCountEntry(b, false);
	Assert(ref != NULL);

	if (fixOwner)
		ResourceOwnerForgetBuffer(CurrentResourceOwner, b);

	Assert(ref->refcount > 0);
	ref->refcount--;
	if (ref->refcount == 0)
	{
		uint32		buf_state;
		uint32		old_buf_state;

		/* I'd better not still hold any locks on the buffer */
		Assert(!LWLockHeldByMe(BufferDescriptorGetContentLock(buf)));
		Assert(!LWLockHeldByMe(BufferDescriptorGetIOLock(buf)));

		/*
		 * Decrement the shared reference count.
		 *
		 * Since buffer spinlock holder can update status using just write,
		 * it's not safe to use atomic decrement here; thus use a CAS loop.
		 */
		old_buf_state = pg_atomic_read_u32(&buf->state);
		for (;;)
		{
			if (old_buf_state & BM_LOCKED)
				old_buf_state = WaitBufHdrUnlocked(buf);

			buf_state = old_buf_state;

			buf_state -= BUF_REFCOUNT_ONE;

			if (pg_atomic_compare_exchange_u32(&buf->state, &old_buf_state,
											   buf_state))
				break;
		}

		/* Support LockBufferForCleanup() */
		if (buf_state & BM_PIN_COUNT_WAITER)
		{
			/*
			 * Acquire the buffer header lock, re-check that there's a waiter.
			 * Another backend could have unpinned this buffer, and already
			 * woken up the waiter.  There's no danger of the buffer being
			 * replaced after we unpinned it above, as it's pinned by the
			 * waiter.
			 */
			buf_state = LockBufHdr(buf);

			if ((buf_state & BM_PIN_COUNT_WAITER) &&
				BUF_STATE_GET_REFCOUNT(buf_state) == 1)
			{
				/* we just released the last pin other than the waiter's */
				int			wait_backend_pid = buf->wait_backend_pid;

				buf_state &= ~BM_PIN_COUNT_WAITER;
				UnlockBufHdr(buf, buf_state);
				ProcSendSignal(wait_backend_pid);
			}
			else
				UnlockBufHdr(buf, buf_state);
		}
		ForgetPrivateRefCountEntry(ref);
	}
}