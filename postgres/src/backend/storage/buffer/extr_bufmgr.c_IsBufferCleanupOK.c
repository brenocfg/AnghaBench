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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  BufferDesc ;
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BUF_STATE_GET_REFCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferDescriptorGetContentLock (int /*<<< orphan*/ *) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int BufferIsValid (int) ; 
 int /*<<< orphan*/ * GetBufferDescriptor (int) ; 
 int GetPrivateRefCount (int) ; 
 int LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int* LocalRefCount ; 
 int /*<<< orphan*/  LockBufHdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockBufHdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
IsBufferCleanupOK(Buffer buffer)
{
	BufferDesc *bufHdr;
	uint32		buf_state;

	Assert(BufferIsValid(buffer));

	if (BufferIsLocal(buffer))
	{
		/* There should be exactly one pin */
		if (LocalRefCount[-buffer - 1] != 1)
			return false;
		/* Nobody else to wait for */
		return true;
	}

	/* There should be exactly one local pin */
	if (GetPrivateRefCount(buffer) != 1)
		return false;

	bufHdr = GetBufferDescriptor(buffer - 1);

	/* caller must hold exclusive lock on buffer */
	Assert(LWLockHeldByMeInMode(BufferDescriptorGetContentLock(bufHdr),
								LW_EXCLUSIVE));

	buf_state = LockBufHdr(bufHdr);

	Assert(BUF_STATE_GET_REFCOUNT(buf_state) > 0);
	if (BUF_STATE_GET_REFCOUNT(buf_state) == 1)
	{
		/* pincount is OK. */
		UnlockBufHdr(bufHdr, buf_state);
		return true;
	}

	UnlockBufHdr(bufHdr, buf_state);
	return false;
}