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
typedef  int /*<<< orphan*/  full_path ;

/* Variables and functions */
 char* DEVNULL ; 
 int MAXCMDLEN ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BACKEND_VERSIONSTR ; 
 char* datadir_target ; 
 scalar_t__ dry_run ; 
 scalar_t__ find_my_exec (char const*,char*) ; 
 int find_other_exec (char const*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_fatal (char*,char*,...) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,char*) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ system (char*) ; 

__attribute__((used)) static void
ensureCleanShutdown(const char *argv0)
{
	int			ret;
#define MAXCMDLEN (2 * MAXPGPATH)
	char		exec_path[MAXPGPATH];
	char		cmd[MAXCMDLEN];

	/* locate postgres binary */
	if ((ret = find_other_exec(argv0, "postgres",
							   PG_BACKEND_VERSIONSTR,
							   exec_path)) < 0)
	{
		char		full_path[MAXPGPATH];

		if (find_my_exec(argv0, full_path) < 0)
			strlcpy(full_path, progname, sizeof(full_path));

		if (ret == -1)
			pg_fatal("The program \"%s\" is needed by %s but was\n"
					 "not found in the same directory as \"%s\".\n"
					 "Check your installation.",
					 "postgres", progname, full_path);
		else
			pg_fatal("The program \"%s\" was found by \"%s\" but was\n"
					 "not the same version as %s.\n"
					 "Check your installation.",
					 "postgres", full_path, progname);
	}

	pg_log_info("executing \"%s\" for target server to complete crash recovery",
				exec_path);

	/*
	 * Skip processing if requested, but only after ensuring presence of
	 * postgres.
	 */
	if (dry_run)
		return;

	/*
	 * Finally run postgres in single-user mode.  There is no need to use
	 * fsync here.  This makes the recovery faster, and the target data folder
	 * is synced at the end anyway.
	 */
	snprintf(cmd, MAXCMDLEN, "\"%s\" --single -F -D \"%s\" template1 < \"%s\"",
			 exec_path, datadir_target, DEVNULL);

	if (system(cmd) != 0)
	{
		pg_log_error("postgres single-user mode of target instance failed");
		pg_fatal("Command was: %s", cmd);
	}
}