#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {scalar_t__ wait_backend_pid; } ;
typedef  TYPE_1__ BufferDesc ;
typedef  int Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BM_PIN_COUNT_WAITER ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int BUF_STATE_GET_REFCOUNT (int) ; 
 scalar_t__ BufferIsLocal (int) ; 
 int BufferIsValid (int) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetBufferDescriptor (int) ; 
 int GetPrivateRefCount (int) ; 
 scalar_t__ InHotStandby ; 
 int* LocalRefCount ; 
 int LockBufHdr (TYPE_1__*) ; 
 int /*<<< orphan*/  LockBuffer (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  PG_WAIT_BUFFER_PIN ; 
 TYPE_1__* PinCountWaitBuf ; 
 int /*<<< orphan*/  ProcWaitForSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithBufferPin () ; 
 int /*<<< orphan*/  SetStartupBufferPinWaitBufId (int) ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

void
LockBufferForCleanup(Buffer buffer)
{
	BufferDesc *bufHdr;

	Assert(BufferIsValid(buffer));
	Assert(PinCountWaitBuf == NULL);

	if (BufferIsLocal(buffer))
	{
		/* There should be exactly one pin */
		if (LocalRefCount[-buffer - 1] != 1)
			elog(ERROR, "incorrect local pin count: %d",
				 LocalRefCount[-buffer - 1]);
		/* Nobody else to wait for */
		return;
	}

	/* There should be exactly one local pin */
	if (GetPrivateRefCount(buffer) != 1)
		elog(ERROR, "incorrect local pin count: %d",
			 GetPrivateRefCount(buffer));

	bufHdr = GetBufferDescriptor(buffer - 1);

	for (;;)
	{
		uint32		buf_state;

		/* Try to acquire lock */
		LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
		buf_state = LockBufHdr(bufHdr);

		Assert(BUF_STATE_GET_REFCOUNT(buf_state) > 0);
		if (BUF_STATE_GET_REFCOUNT(buf_state) == 1)
		{
			/* Successfully acquired exclusive lock with pincount 1 */
			UnlockBufHdr(bufHdr, buf_state);
			return;
		}
		/* Failed, so mark myself as waiting for pincount 1 */
		if (buf_state & BM_PIN_COUNT_WAITER)
		{
			UnlockBufHdr(bufHdr, buf_state);
			LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
			elog(ERROR, "multiple backends attempting to wait for pincount 1");
		}
		bufHdr->wait_backend_pid = MyProcPid;
		PinCountWaitBuf = bufHdr;
		buf_state |= BM_PIN_COUNT_WAITER;
		UnlockBufHdr(bufHdr, buf_state);
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);

		/* Wait to be signaled by UnpinBuffer() */
		if (InHotStandby)
		{
			/* Publish the bufid that Startup process waits on */
			SetStartupBufferPinWaitBufId(buffer - 1);
			/* Set alarm and then wait to be signaled by UnpinBuffer() */
			ResolveRecoveryConflictWithBufferPin();
			/* Reset the published bufid */
			SetStartupBufferPinWaitBufId(-1);
		}
		else
			ProcWaitForSignal(PG_WAIT_BUFFER_PIN);

		/*
		 * Remove flag marking us as waiter. Normally this will not be set
		 * anymore, but ProcWaitForSignal() can return for other signals as
		 * well.  We take care to only reset the flag if we're the waiter, as
		 * theoretically another backend could have started waiting. That's
		 * impossible with the current usages due to table level locking, but
		 * better be safe.
		 */
		buf_state = LockBufHdr(bufHdr);
		if ((buf_state & BM_PIN_COUNT_WAITER) != 0 &&
			bufHdr->wait_backend_pid == MyProcPid)
			buf_state &= ~BM_PIN_COUNT_WAITER;
		UnlockBufHdr(bufHdr, buf_state);

		PinCountWaitBuf = NULL;
		/* Loop back and try again */
	}
}