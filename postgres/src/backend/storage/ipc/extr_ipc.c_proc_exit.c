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
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  proc_exit_prepare (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void
proc_exit(int code)
{
	/* Clean up everything that must be cleaned up */
	proc_exit_prepare(code);

#ifdef PROFILE_PID_DIR
	{
		/*
		 * If we are profiling ourself then gprof's mcleanup() is about to
		 * write out a profile to ./gmon.out.  Since mcleanup() always uses a
		 * fixed file name, each backend will overwrite earlier profiles. To
		 * fix that, we create a separate subdirectory for each backend
		 * (./gprof/pid) and 'cd' to that subdirectory before we exit() - that
		 * forces mcleanup() to write each profile into its own directory.  We
		 * end up with something like: $PGDATA/gprof/8829/gmon.out
		 * $PGDATA/gprof/8845/gmon.out ...
		 *
		 * To avoid undesirable disk space bloat, autovacuum workers are
		 * discriminated against: all their gmon.out files go into the same
		 * subdirectory.  Without this, an installation that is "just sitting
		 * there" nonetheless eats megabytes of disk space every few seconds.
		 *
		 * Note that we do this here instead of in an on_proc_exit() callback
		 * because we want to ensure that this code executes last - we don't
		 * want to interfere with any other on_proc_exit() callback.  For the
		 * same reason, we do not include it in proc_exit_prepare ... so if
		 * you are exiting in the "wrong way" you won't drop your profile in a
		 * nice place.
		 */
		char		gprofDirName[32];

		if (IsAutoVacuumWorkerProcess())
			snprintf(gprofDirName, 32, "gprof/avworker");
		else
			snprintf(gprofDirName, 32, "gprof/%d", (int) getpid());

		/*
		 * Use mkdir() instead of MakePGDirectory() since we aren't making a
		 * PG directory here.
		 */
		mkdir("gprof", S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir(gprofDirName, S_IRWXU | S_IRWXG | S_IRWXO);
		chdir(gprofDirName);
	}
#endif

	elog(DEBUG3, "exit(%d)", code);

	exit(code);
}