#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pgdata; scalar_t__ bindir; } ;
struct TYPE_5__ {int /*<<< orphan*/  check; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  check_pghost_envvar () ; 
 scalar_t__ find_my_exec (char*,char*) ; 
 char* last_dir_separator (char*) ; 
 TYPE_2__ new_cluster ; 
 TYPE_2__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 scalar_t__ pg_strdup (char*) ; 
 scalar_t__ pid_lock_file_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ start_postmaster (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stop_postmaster (int) ; 
 TYPE_1__ user_opts ; 
 int /*<<< orphan*/  verify_directories () ; 

__attribute__((used)) static void
setup(char *argv0, bool *live_check)
{
	/*
	 * make sure the user has a clean environment, otherwise, we may confuse
	 * libpq when we connect to one (or both) of the servers.
	 */
	check_pghost_envvar();

	/*
	 * In case the user hasn't specified the directory for the new binaries
	 * with -B, default to using the path of the currently executed pg_upgrade
	 * binary.
	 */
	if (!new_cluster.bindir)
	{
		char		exec_path[MAXPGPATH];

		if (find_my_exec(argv0, exec_path) < 0)
			pg_fatal("%s: could not find own program executable\n", argv0);
		/* Trim off program name and keep just path */
		*last_dir_separator(exec_path) = '\0';
		canonicalize_path(exec_path);
		new_cluster.bindir = pg_strdup(exec_path);
	}

	verify_directories();

	/* no postmasters should be running, except for a live check */
	if (pid_lock_file_exists(old_cluster.pgdata))
	{
		/*
		 * If we have a postmaster.pid file, try to start the server.  If it
		 * starts, the pid file was stale, so stop the server.  If it doesn't
		 * start, assume the server is running.  If the pid file is left over
		 * from a server crash, this also allows any committed transactions
		 * stored in the WAL to be replayed so they are not lost, because WAL
		 * files are not transferred from old to new servers.  We later check
		 * for a clean shutdown.
		 */
		if (start_postmaster(&old_cluster, false))
			stop_postmaster(false);
		else
		{
			if (!user_opts.check)
				pg_fatal("There seems to be a postmaster servicing the old cluster.\n"
						 "Please shutdown that postmaster and try again.\n");
			else
				*live_check = true;
		}
	}

	/* same goes for the new postmaster */
	if (pid_lock_file_exists(new_cluster.pgdata))
	{
		if (start_postmaster(&new_cluster, false))
			stop_postmaster(false);
		else
			pg_fatal("There seems to be a postmaster servicing the new cluster.\n"
					 "Please shutdown that postmaster and try again.\n");
	}
}