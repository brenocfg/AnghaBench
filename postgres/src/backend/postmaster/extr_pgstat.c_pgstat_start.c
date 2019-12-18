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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePostmasterPorts (int) ; 
 int /*<<< orphan*/  InitPostmasterChild () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ PGINVALID_SOCKET ; 
 scalar_t__ PGSTAT_RESTART_INTERVAL ; 
 int /*<<< orphan*/  PGSharedMemoryDetach () ; 
 int /*<<< orphan*/  PgstatCollectorMain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_detach_all () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ fork_process () ; 
 scalar_t__ last_pgstat_start_time ; 
 scalar_t__ pgStatSock ; 
 scalar_t__ pgstat_forkexec () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
pgstat_start(void)
{
	time_t		curtime;
	pid_t		pgStatPid;

	/*
	 * Check that the socket is there, else pgstat_init failed and we can do
	 * nothing useful.
	 */
	if (pgStatSock == PGINVALID_SOCKET)
		return 0;

	/*
	 * Do nothing if too soon since last collector start.  This is a safety
	 * valve to protect against continuous respawn attempts if the collector
	 * is dying immediately at launch.  Note that since we will be re-called
	 * from the postmaster main loop, we will get another chance later.
	 */
	curtime = time(NULL);
	if ((unsigned int) (curtime - last_pgstat_start_time) <
		(unsigned int) PGSTAT_RESTART_INTERVAL)
		return 0;
	last_pgstat_start_time = curtime;

	/*
	 * Okay, fork off the collector.
	 */
#ifdef EXEC_BACKEND
	switch ((pgStatPid = pgstat_forkexec()))
#else
	switch ((pgStatPid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork statistics collector: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:
			/* in postmaster child ... */
			InitPostmasterChild();

			/* Close the postmaster's sockets */
			ClosePostmasterPorts(false);

			/* Drop our connection to postmaster's shared memory, as well */
			dsm_detach_all();
			PGSharedMemoryDetach();

			PgstatCollectorMain(0, NULL);
			break;
#endif

		default:
			return (int) pgStatPid;
	}

	/* shouldn't get here */
	return 0;
}