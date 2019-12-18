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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  selfpipe_readfd ; 
 int waiting ; 

__attribute__((used)) static void
drainSelfPipe(void)
{
	/*
	 * There shouldn't normally be more than one byte in the pipe, or maybe a
	 * few bytes if multiple processes run SetLatch at the same instant.
	 */
	char		buf[16];
	int			rc;

	for (;;)
	{
		rc = read(selfpipe_readfd, buf, sizeof(buf));
		if (rc < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;			/* the pipe is empty */
			else if (errno == EINTR)
				continue;		/* retry */
			else
			{
				waiting = false;
				elog(ERROR, "read() on self-pipe failed: %m");
			}
		}
		else if (rc == 0)
		{
			waiting = false;
			elog(ERROR, "unexpected EOF on self-pipe");
		}
		else if (rc < sizeof(buf))
		{
			/* we successfully drained the pipe; no need to read() again */
			break;
		}
		/* else buffer wasn't big enough, so read again */
	}
}