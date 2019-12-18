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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ pgpid_t ;

/* Variables and functions */
 scalar_t__ DB_IN_ARCHIVE_RECOVERY ; 
 scalar_t__ SMART_MODE ; 
 int USEC_PER_SEC ; 
 int WAITS_PER_SEC ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  backup_file ; 
 int /*<<< orphan*/  do_start () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_control_dbstate () ; 
 scalar_t__ get_pgpid (int) ; 
 scalar_t__ kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (int) ; 
 int /*<<< orphan*/  pid_file ; 
 scalar_t__ postmaster_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_msg (char*) ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ shutdown_mode ; 
 int /*<<< orphan*/  sig ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int wait_seconds ; 
 int /*<<< orphan*/  write_stderr (char*,...) ; 

__attribute__((used)) static void
do_restart(void)
{
	int			cnt;
	pgpid_t		pid;
	struct stat statbuf;

	pid = get_pgpid(false);

	if (pid == 0)				/* no pid file */
	{
		write_stderr(_("%s: PID file \"%s\" does not exist\n"),
					 progname, pid_file);
		write_stderr(_("Is server running?\n"));
		write_stderr(_("trying to start server anyway\n"));
		do_start();
		return;
	}
	else if (pid < 0)			/* standalone backend, not postmaster */
	{
		pid = -pid;
		if (postmaster_is_alive((pid_t) pid))
		{
			write_stderr(_("%s: cannot restart server; "
						   "single-user server is running (PID: %ld)\n"),
						 progname, pid);
			write_stderr(_("Please terminate the single-user server and try again.\n"));
			exit(1);
		}
	}

	if (postmaster_is_alive((pid_t) pid))
	{
		if (kill((pid_t) pid, sig) != 0)
		{
			write_stderr(_("%s: could not send stop signal (PID: %ld): %s\n"), progname, pid,
						 strerror(errno));
			exit(1);
		}

		/*
		 * If backup_label exists, an online backup is running. Warn the user
		 * that smart shutdown will wait for it to finish. However, if the
		 * server is in archive recovery, we're recovering from an online
		 * backup instead of performing one.
		 */
		if (shutdown_mode == SMART_MODE &&
			stat(backup_file, &statbuf) == 0 &&
			get_control_dbstate() != DB_IN_ARCHIVE_RECOVERY)
		{
			print_msg(_("WARNING: online backup mode is active\n"
						"Shutdown will not complete until pg_stop_backup() is called.\n\n"));
		}

		print_msg(_("waiting for server to shut down..."));

		/* always wait for restart */

		for (cnt = 0; cnt < wait_seconds * WAITS_PER_SEC; cnt++)
		{
			if ((pid = get_pgpid(false)) != 0)
			{
				if (cnt % WAITS_PER_SEC == 0)
					print_msg(".");
				pg_usleep(USEC_PER_SEC / WAITS_PER_SEC);
			}
			else
				break;
		}

		if (pid != 0)			/* pid file still exists */
		{
			print_msg(_(" failed\n"));

			write_stderr(_("%s: server does not shut down\n"), progname);
			if (shutdown_mode == SMART_MODE)
				write_stderr(_("HINT: The \"-m fast\" option immediately disconnects sessions rather than\n"
							   "waiting for session-initiated disconnection.\n"));
			exit(1);
		}

		print_msg(_(" done\n"));
		print_msg(_("server stopped\n"));
	}
	else
	{
		write_stderr(_("%s: old server process (PID: %ld) seems to be gone\n"),
					 progname, pid);
		write_stderr(_("starting server anyway\n"));
	}

	do_start();
}