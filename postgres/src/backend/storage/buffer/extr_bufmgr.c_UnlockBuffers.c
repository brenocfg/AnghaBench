#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_5__ {scalar_t__ wait_backend_pid; } ;
typedef  TYPE_1__ BufferDesc ;

/* Variables and functions */
 int BM_PIN_COUNT_WAITER ; 
 int LockBufHdr (TYPE_1__*) ; 
 scalar_t__ MyProcPid ; 
 TYPE_1__* PinCountWaitBuf ; 
 int /*<<< orphan*/  UnlockBufHdr (TYPE_1__*,int) ; 

void
UnlockBuffers(void)
{
	BufferDesc *buf = PinCountWaitBuf;

	if (buf)
	{
		uint32		buf_state;

		buf_state = LockBufHdr(buf);

		/*
		 * Don't complain if flag bit not set; it could have been reset but we
		 * got a cancel/die interrupt before getting the signal.
		 */
		if ((buf_state & BM_PIN_COUNT_WAITER) != 0 &&
			buf->wait_backend_pid == MyProcPid)
			buf_state &= ~BM_PIN_COUNT_WAITER;

		UnlockBufHdr(buf, buf_state);

		PinCountWaitBuf = NULL;
	}
}