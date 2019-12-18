#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_10__ {int events; } ;
typedef  TYPE_2__ WaitEvent ;
struct TYPE_11__ {int /*<<< orphan*/  noblock; TYPE_1__* gss; scalar_t__ ssl_in_use; } ;
struct TYPE_9__ {scalar_t__ enc; } ;
typedef  TYPE_3__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  ERRCODE_ADMIN_SHUTDOWN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  FeBeWaitSet ; 
 int /*<<< orphan*/  ModifyWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ProcessClientWriteInterrupt (int) ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_CLIENT_WRITE ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_SOCKET_WRITEABLE ; 
 int /*<<< orphan*/  WaitEventSetWait (int /*<<< orphan*/ ,int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ be_gssapi_write (TYPE_3__*,void*,size_t) ; 
 scalar_t__ be_tls_write (TYPE_3__*,void*,size_t,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ secure_raw_write (TYPE_3__*,void*,size_t) ; 

ssize_t
secure_write(Port *port, void *ptr, size_t len)
{
	ssize_t		n;
	int			waitfor;

	/* Deal with any already-pending interrupt condition. */
	ProcessClientWriteInterrupt(false);

retry:
	waitfor = 0;
#ifdef USE_SSL
	if (port->ssl_in_use)
	{
		n = be_tls_write(port, ptr, len, &waitfor);
	}
	else
#endif
#ifdef ENABLE_GSS
	if (port->gss->enc)
	{
		n = be_gssapi_write(port, ptr, len);
		waitfor = WL_SOCKET_WRITEABLE;
	}
	else
#endif
	{
		n = secure_raw_write(port, ptr, len);
		waitfor = WL_SOCKET_WRITEABLE;
	}

	if (n < 0 && !port->noblock && (errno == EWOULDBLOCK || errno == EAGAIN))
	{
		WaitEvent	event;

		Assert(waitfor);

		ModifyWaitEvent(FeBeWaitSet, 0, waitfor, NULL);

		WaitEventSetWait(FeBeWaitSet, -1 /* no timeout */ , &event, 1,
						 WAIT_EVENT_CLIENT_WRITE);

		/* See comments in secure_read. */
		if (event.events & WL_POSTMASTER_DEATH)
			ereport(FATAL,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("terminating connection due to unexpected postmaster exit")));

		/* Handle interrupt. */
		if (event.events & WL_LATCH_SET)
		{
			ResetLatch(MyLatch);
			ProcessClientWriteInterrupt(true);

			/*
			 * We'll retry the write. Most likely it will return immediately
			 * because there's still no buffer space available, and we'll wait
			 * for the socket to become ready again.
			 */
		}
		goto retry;
	}

	/*
	 * Process interrupts that happened during a successful (or non-blocking,
	 * or hard-failed) write.
	 */
	ProcessClientWriteInterrupt(false);

	return n;
}