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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  BufferDesc ;
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int BUF_STATE_GET_REFCOUNT (int) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int BufferIsValid (int) ; 
 int /*<<< orphan*/  ConditionalLockBuffer (int) ; 
 int /*<<< orphan*/ * GetBufferDescriptor (int) ; 
 int GetPrivateRefCount (int) ; 
 int* LocalRefCount ; 
 int LockBufHdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockBufHdr (int /*<<< orphan*/ *,int) ; 

bool
ConditionalLockBufferForCleanup(Buffer buffer)
{
	BufferDesc *bufHdr;
	uint32		buf_state,
				refcount;

	Assert(BufferIsValid(buffer));

	if (BufferIsLocal(buffer))
	{
		refcount = LocalRefCount[-buffer - 1];
		/* There should be exactly one pin */
		Assert(refcount > 0);
		if (refcount != 1)
			return false;
		/* Nobody else to wait for */
		return true;
	}

	/* There should be exactly one local pin */
	refcount = GetPrivateRefCount(buffer);
	Assert(refcount);
	if (refcount != 1)
		return false;

	/* Try to acquire lock */
	if (!ConditionalLockBuffer(buffer))
		return false;

	bufHdr = GetBufferDescriptor(buffer - 1);
	buf_state = LockBufHdr(bufHdr);
	refcount = BUF_STATE_GET_REFCOUNT(buf_state);

	Assert(refcount > 0);
	if (refcount == 1)
	{
		/* Successfully acquired exclusive lock with pincount 1 */
		UnlockBufHdr(bufHdr, buf_state);
		return true;
	}

	/* Failed, so release the lock */
	UnlockBufHdr(bufHdr, buf_state);
	LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
	return false;
}