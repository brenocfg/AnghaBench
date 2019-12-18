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
typedef  scalar_t__ pgpid_t ;
typedef  int /*<<< orphan*/  env_var ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PG_BACKEND_VERSIONSTR ; 
#define  POSTMASTER_FAILED 130 
#define  POSTMASTER_READY 129 
#define  POSTMASTER_STILL_STARTING 128 
 scalar_t__ RESTART_COMMAND ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ allow_core_files ; 
 int /*<<< orphan*/  argv0 ; 
 scalar_t__ ctl_command ; 
 scalar_t__ do_wait ; 
 int /*<<< orphan*/ * exec_path ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * find_other_exec_or_die (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_pgpid (int) ; 
 scalar_t__ getppid () ; 
 char* pgdata_opt ; 
 scalar_t__ postmasterPID ; 
 int /*<<< orphan*/  postmasterProcess ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  read_post_opts () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ start_postmaster () ; 
 int /*<<< orphan*/  trap_sigint_during_startup ; 
 int /*<<< orphan*/  unlimit_core_size () ; 
 int wait_for_postmaster (scalar_t__,int) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_start(void)
{
	pgpid_t		old_pid = 0;
	pgpid_t		pm_pid;

	if (ctl_command != RESTART_COMMAND)
	{
		old_pid = get_pgpid(false);
		if (old_pid != 0)
			write_stderr(_("%s: another server might be running; "
						   "trying to start server anyway\n"),
						 progname);
	}

	read_post_opts();

	/* No -D or -D already added during server start */
	if (ctl_command == RESTART_COMMAND || pgdata_opt == NULL)
		pgdata_opt = "";

	if (exec_path == NULL)
		exec_path = find_other_exec_or_die(argv0, "postgres", PG_BACKEND_VERSIONSTR);

#if defined(HAVE_GETRLIMIT) && defined(RLIMIT_CORE)
	if (allow_core_files)
		unlimit_core_size();
#endif

	/*
	 * If possible, tell the postmaster our parent shell's PID (see the
	 * comments in CreateLockFile() for motivation).  Windows hasn't got
	 * getppid() unfortunately.
	 */
#ifndef WIN32
	{
		static char env_var[32];

		snprintf(env_var, sizeof(env_var), "PG_GRANDPARENT_PID=%d",
				 (int) getppid());
		putenv(env_var);
	}
#endif

	pm_pid = start_postmaster();

	if (do_wait)
	{
		/*
		 * If the user interrupts the startup (e.g. with CTRL-C), we'd like to
		 * abort the server launch.  Install a signal handler that will
		 * forward SIGINT to the postmaster process, while we wait.
		 *
		 * (We don't bother to reset the signal handler after the launch, as
		 * we're about to exit, anyway.)
		 */
		postmasterPID = pm_pid;
		pqsignal(SIGINT, trap_sigint_during_startup);

		print_msg(_("waiting for server to start..."));

		switch (wait_for_postmaster(pm_pid, false))
		{
			case POSTMASTER_READY:
				print_msg(_(" done\n"));
				print_msg(_("server started\n"));
				break;
			case POSTMASTER_STILL_STARTING:
				print_msg(_(" stopped waiting\n"));
				write_stderr(_("%s: server did not start in time\n"),
							 progname);
				exit(1);
				break;
			case POSTMASTER_FAILED:
				print_msg(_(" stopped waiting\n"));
				write_stderr(_("%s: could not start server\n"
							   "Examine the log output.\n"),
							 progname);
				exit(1);
				break;
		}
	}
	else
		print_msg(_("server starting\n"));

#ifdef WIN32
	/* Now we don't need the handle to the shell process anymore */
	CloseHandle(postmasterProcess);
	postmasterProcess = INVALID_HANDLE_VALUE;
#endif
}