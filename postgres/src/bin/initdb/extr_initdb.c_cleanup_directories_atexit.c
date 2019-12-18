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
 scalar_t__ found_existing_pgdata ; 
 scalar_t__ found_existing_xlogdir ; 
 scalar_t__ made_new_pgdata ; 
 scalar_t__ made_new_xlogdir ; 
 int /*<<< orphan*/  noclean ; 
 int /*<<< orphan*/  pg_data ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmtree (int /*<<< orphan*/ ,int) ; 
 scalar_t__ success ; 
 int /*<<< orphan*/  xlog_dir ; 

__attribute__((used)) static void
cleanup_directories_atexit(void)
{
	if (success)
		return;

	if (!noclean)
	{
		if (made_new_pgdata)
		{
			pg_log_info("removing data directory \"%s\"", pg_data);
			if (!rmtree(pg_data, true))
				pg_log_error("failed to remove data directory");
		}
		else if (found_existing_pgdata)
		{
			pg_log_info("removing contents of data directory \"%s\"",
						pg_data);
			if (!rmtree(pg_data, false))
				pg_log_error("failed to remove contents of data directory");
		}

		if (made_new_xlogdir)
		{
			pg_log_info("removing WAL directory \"%s\"", xlog_dir);
			if (!rmtree(xlog_dir, true))
				pg_log_error("failed to remove WAL directory");
		}
		else if (found_existing_xlogdir)
		{
			pg_log_info("removing contents of WAL directory \"%s\"", xlog_dir);
			if (!rmtree(xlog_dir, false))
				pg_log_error("failed to remove contents of WAL directory");
		}
		/* otherwise died during startup, do nothing! */
	}
	else
	{
		if (made_new_pgdata || found_existing_pgdata)
			pg_log_info("data directory \"%s\" not removed at user's request",
						pg_data);

		if (made_new_xlogdir || found_existing_xlogdir)
			pg_log_info("WAL directory \"%s\" not removed at user's request",
						xlog_dir);
	}
}