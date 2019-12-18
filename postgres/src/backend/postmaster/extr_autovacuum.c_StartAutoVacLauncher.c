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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AutoVacLauncherMain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClosePostmasterPorts (int) ; 
 int /*<<< orphan*/  InitPostmasterChild () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ avlauncher_forkexec () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ fork_process () ; 

int
StartAutoVacLauncher(void)
{
	pid_t		AutoVacPID;

#ifdef EXEC_BACKEND
	switch ((AutoVacPID = avlauncher_forkexec()))
#else
	switch ((AutoVacPID = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork autovacuum launcher process: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:
			/* in postmaster child ... */
			InitPostmasterChild();

			/* Close the postmaster's sockets */
			ClosePostmasterPorts(false);

			AutoVacLauncherMain(0, NULL);
			break;
#endif
		default:
			return (int) AutoVacPID;
	}

	/* shouldn't get here */
	return 0;
}