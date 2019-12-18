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
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  InitLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitProcessGlobals () ; 
 int /*<<< orphan*/  InitializeLatchSupport () ; 
 int IsUnderPostmaster ; 
 int /*<<< orphan*/  LocalLatchData ; 
 int /*<<< orphan*/ * MyLatch ; 
 int /*<<< orphan*/  PostmasterDeathSignalInit () ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_exit_reset () ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  stderr ; 

void
InitPostmasterChild(void)
{
	IsUnderPostmaster = true;	/* we are a postmaster subprocess now */

	InitProcessGlobals();

	/*
	 * make sure stderr is in binary mode before anything can possibly be
	 * written to it, in case it's actually the syslogger pipe, so the pipe
	 * chunking protocol isn't disturbed. Non-logpipe data gets translated on
	 * redirection (e.g. via pg_ctl -l) anyway.
	 */
#ifdef WIN32
	_setmode(fileno(stderr), _O_BINARY);
#endif

	/* We don't want the postmaster's proc_exit() handlers */
	on_exit_reset();

	/* Initialize process-local latch support */
	InitializeLatchSupport();
	MyLatch = &LocalLatchData;
	InitLatch(MyLatch);

	/*
	 * If possible, make this process a group leader, so that the postmaster
	 * can signal any child processes too. Not all processes will have
	 * children, but for consistency we make all postmaster child processes do
	 * this.
	 */
#ifdef HAVE_SETSID
	if (setsid() < 0)
		elog(FATAL, "setsid() failed: %m");
#endif

	/* Request a signal if the postmaster dies, if possible. */
	PostmasterDeathSignalInit();
}