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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_DIRTY ; 
 int BM_IO_IN_PROGRESS ; 
 int BM_VALID ; 
 int /*<<< orphan*/  BufferDescriptorGetIOLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InProgressBuf ; 
 int IsForInput ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int LockBufHdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockBufHdr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WaitIO (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
StartBufferIO(BufferDesc *buf, bool forInput)
{
	uint32		buf_state;

	Assert(!InProgressBuf);

	for (;;)
	{
		/*
		 * Grab the io_in_progress lock so that other processes can wait for
		 * me to finish the I/O.
		 */
		LWLockAcquire(BufferDescriptorGetIOLock(buf), LW_EXCLUSIVE);

		buf_state = LockBufHdr(buf);

		if (!(buf_state & BM_IO_IN_PROGRESS))
			break;

		/*
		 * The only way BM_IO_IN_PROGRESS could be set when the io_in_progress
		 * lock isn't held is if the process doing the I/O is recovering from
		 * an error (see AbortBufferIO).  If that's the case, we must wait for
		 * him to get unwedged.
		 */
		UnlockBufHdr(buf, buf_state);
		LWLockRelease(BufferDescriptorGetIOLock(buf));
		WaitIO(buf);
	}

	/* Once we get here, there is definitely no I/O active on this buffer */

	if (forInput ? (buf_state & BM_VALID) : !(buf_state & BM_DIRTY))
	{
		/* someone else already did the I/O */
		UnlockBufHdr(buf, buf_state);
		LWLockRelease(BufferDescriptorGetIOLock(buf));
		return false;
	}

	buf_state |= BM_IO_IN_PROGRESS;
	UnlockBufHdr(buf, buf_state);

	InProgressBuf = buf;
	IsForInput = forInput;

	return true;
}