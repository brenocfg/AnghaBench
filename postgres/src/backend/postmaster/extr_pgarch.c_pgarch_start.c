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
 scalar_t__ PGARCH_RESTART_INTERVAL ; 
 int /*<<< orphan*/  PGSharedMemoryDetach () ; 
 int /*<<< orphan*/  PgArchiverMain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogArchivingActive () ; 
 int /*<<< orphan*/  dsm_detach_all () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ fork_process () ; 
 scalar_t__ last_pgarch_start_time ; 
 scalar_t__ pgarch_forkexec () ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
pgarch_start(void)
{
	time_t		curtime;
	pid_t		pgArchPid;

	/*
	 * Do nothing if no archiver needed
	 */
	if (!XLogArchivingActive())
		return 0;

	/*
	 * Do nothing if too soon since last archiver start.  This is a safety
	 * valve to protect against continuous respawn attempts if the archiver is
	 * dying immediately at launch. Note that since we will be re-called from
	 * the postmaster main loop, we will get another chance later.
	 */
	curtime = time(NULL);
	if ((unsigned int) (curtime - last_pgarch_start_time) <
		(unsigned int) PGARCH_RESTART_INTERVAL)
		return 0;
	last_pgarch_start_time = curtime;

#ifdef EXEC_BACKEND
	switch ((pgArchPid = pgarch_forkexec()))
#else
	switch ((pgArchPid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork archiver: %m")));
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

			PgArchiverMain(0, NULL);
			break;
#endif

		default:
			return (int) pgArchPid;
	}

	/* shouldn't get here */
	return 0;
}