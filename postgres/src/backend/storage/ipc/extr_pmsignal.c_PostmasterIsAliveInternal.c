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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FATAL ; 
 size_t POSTMASTER_FD_WATCH ; 
 int /*<<< orphan*/  PostmasterHandle ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * postmaster_alive_fds ; 
 int postmaster_possibly_dead ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 

bool
PostmasterIsAliveInternal(void)
{
#ifdef USE_POSTMASTER_DEATH_SIGNAL
	/*
	 * Reset the flag before checking, so that we don't miss a signal if
	 * postmaster dies right after the check.  If postmaster was indeed dead,
	 * we'll re-arm it before returning to caller.
	 */
	postmaster_possibly_dead = false;
#endif

#ifndef WIN32
	{
		char		c;
		ssize_t		rc;

		rc = read(postmaster_alive_fds[POSTMASTER_FD_WATCH], &c, 1);

		/*
		 * In the usual case, the postmaster is still alive, and there is no
		 * data in the pipe.
		 */
		if (rc < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return true;
		else
		{
			/*
			 * Postmaster is dead, or something went wrong with the read()
			 * call.
			 */

#ifdef USE_POSTMASTER_DEATH_SIGNAL
			postmaster_possibly_dead = true;
#endif

			if (rc < 0)
				elog(FATAL, "read on postmaster death monitoring pipe failed: %m");
			else if (rc > 0)
				elog(FATAL, "unexpected data in postmaster death monitoring pipe");

			return false;
		}
	}

#else							/* WIN32 */
	if (WaitForSingleObject(PostmasterHandle, 0) == WAIT_TIMEOUT)
		return true;
	else
	{
#ifdef USE_POSTMASTER_DEATH_SIGNAL
		postmaster_possibly_dead = true;
#endif
		return false;
	}
#endif							/* WIN32 */
}