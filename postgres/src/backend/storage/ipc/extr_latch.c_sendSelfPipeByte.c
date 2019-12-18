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

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  selfpipe_writefd ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
sendSelfPipeByte(void)
{
	int			rc;
	char		dummy = 0;

retry:
	rc = write(selfpipe_writefd, &dummy, 1);
	if (rc < 0)
	{
		/* If interrupted by signal, just retry */
		if (errno == EINTR)
			goto retry;

		/*
		 * If the pipe is full, we don't need to retry, the data that's there
		 * already is enough to wake up WaitLatch.
		 */
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;

		/*
		 * Oops, the write() failed for some other reason. We might be in a
		 * signal handler, so it's not safe to elog(). We have no choice but
		 * silently ignore the error.
		 */
		return;
	}
}