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
typedef  scalar_t__ time_t ;
typedef  int pg_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  MyLatch ; 
 int PGARCH_AUTOWAKE_INTERVAL ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_ARCHIVER_MAIN ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_TIMEOUT ; 
 int WaitLatch (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int got_SIGHUP ; 
 scalar_t__ got_SIGTERM ; 
 scalar_t__ last_sigterm_time ; 
 int /*<<< orphan*/  pgarch_ArchiverCopyLoop () ; 
 int ready_to_stop ; 
 void* time (int /*<<< orphan*/ *) ; 
 int wakened ; 

__attribute__((used)) static void
pgarch_MainLoop(void)
{
	pg_time_t	last_copy_time = 0;
	bool		time_to_stop;

	/*
	 * We run the copy loop immediately upon entry, in case there are
	 * unarchived files left over from a previous database run (or maybe the
	 * archiver died unexpectedly).  After that we wait for a signal or
	 * timeout before doing more.
	 */
	wakened = true;

	/*
	 * There shouldn't be anything for the archiver to do except to wait for a
	 * signal ... however, the archiver exists to protect our data, so she
	 * wakes up occasionally to allow herself to be proactive.
	 */
	do
	{
		ResetLatch(MyLatch);

		/* When we get SIGUSR2, we do one more archive cycle, then exit */
		time_to_stop = ready_to_stop;

		/* Check for config update */
		if (got_SIGHUP)
		{
			got_SIGHUP = false;
			ProcessConfigFile(PGC_SIGHUP);
		}

		/*
		 * If we've gotten SIGTERM, we normally just sit and do nothing until
		 * SIGUSR2 arrives.  However, that means a random SIGTERM would
		 * disable archiving indefinitely, which doesn't seem like a good
		 * idea.  If more than 60 seconds pass since SIGTERM, exit anyway, so
		 * that the postmaster can start a new archiver if needed.
		 */
		if (got_SIGTERM)
		{
			time_t		curtime = time(NULL);

			if (last_sigterm_time == 0)
				last_sigterm_time = curtime;
			else if ((unsigned int) (curtime - last_sigterm_time) >=
					 (unsigned int) 60)
				break;
		}

		/* Do what we're here for */
		if (wakened || time_to_stop)
		{
			wakened = false;
			pgarch_ArchiverCopyLoop();
			last_copy_time = time(NULL);
		}

		/*
		 * Sleep until a signal is received, or until a poll is forced by
		 * PGARCH_AUTOWAKE_INTERVAL having passed since last_copy_time, or
		 * until postmaster dies.
		 */
		if (!time_to_stop)		/* Don't wait during last iteration */
		{
			pg_time_t	curtime = (pg_time_t) time(NULL);
			int			timeout;

			timeout = PGARCH_AUTOWAKE_INTERVAL - (curtime - last_copy_time);
			if (timeout > 0)
			{
				int			rc;

				rc = WaitLatch(MyLatch,
							   WL_LATCH_SET | WL_TIMEOUT | WL_POSTMASTER_DEATH,
							   timeout * 1000L,
							   WAIT_EVENT_ARCHIVER_MAIN);
				if (rc & WL_TIMEOUT)
					wakened = true;
				if (rc & WL_POSTMASTER_DEATH)
					time_to_stop = true;
			}
			else
				wakened = true;
		}

		/*
		 * The archiver quits either when the postmaster dies (not expected)
		 * or after completing one more archiving cycle after receiving
		 * SIGUSR2.
		 */
	} while (!time_to_stop);
}