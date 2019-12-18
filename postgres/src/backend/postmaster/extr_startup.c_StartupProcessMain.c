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
 int /*<<< orphan*/  InitializeTimeouts () ; 
 int /*<<< orphan*/  PG_SETMASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STANDBY_DEADLOCK_TIMEOUT ; 
 int /*<<< orphan*/  STANDBY_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  STANDBY_TIMEOUT ; 
 int /*<<< orphan*/  StandbyDeadLockHandler ; 
 int /*<<< orphan*/  StandbyLockTimeoutHandler ; 
 int /*<<< orphan*/  StandbyTimeoutHandler ; 
 int /*<<< orphan*/  StartupProcShutdownHandler ; 
 int /*<<< orphan*/  StartupProcSigHupHandler ; 
 int /*<<< orphan*/  StartupProcSigUsr1Handler ; 
 int /*<<< orphan*/  StartupProcTriggerHandler ; 
 int /*<<< orphan*/  StartupXLOG () ; 
 int /*<<< orphan*/  UnBlockSig ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startupproc_quickdie ; 

void
StartupProcessMain(void)
{
	/*
	 * Properly accept or ignore signals the postmaster might send us.
	 */
	pqsignal(SIGHUP, StartupProcSigHupHandler); /* reload config file */
	pqsignal(SIGINT, SIG_IGN);	/* ignore query cancel */
	pqsignal(SIGTERM, StartupProcShutdownHandler);	/* request shutdown */
	pqsignal(SIGQUIT, startupproc_quickdie);	/* hard crash time */
	InitializeTimeouts();		/* establishes SIGALRM handler */
	pqsignal(SIGPIPE, SIG_IGN);
	pqsignal(SIGUSR1, StartupProcSigUsr1Handler);
	pqsignal(SIGUSR2, StartupProcTriggerHandler);

	/*
	 * Reset some signals that are accepted by postmaster but not here
	 */
	pqsignal(SIGCHLD, SIG_DFL);

	/*
	 * Register timeouts needed for standby mode
	 */
	RegisterTimeout(STANDBY_DEADLOCK_TIMEOUT, StandbyDeadLockHandler);
	RegisterTimeout(STANDBY_TIMEOUT, StandbyTimeoutHandler);
	RegisterTimeout(STANDBY_LOCK_TIMEOUT, StandbyLockTimeoutHandler);

	/*
	 * Unblock signals (they were blocked when the postmaster forked us)
	 */
	PG_SETMASK(&UnBlockSig);

	/*
	 * Do what we came for.
	 */
	StartupXLOG();

	/*
	 * Exit normally. Exit code 0 tells postmaster that we completed recovery
	 * successfully.
	 */
	proc_exit(0);
}