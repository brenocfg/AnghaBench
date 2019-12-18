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
 char* _ (char*) ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 char* pg_data ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 void* pg_strdup (char*) ; 
 void* pgdata_native ; 
 char* psprintf (char*,char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 

void
setup_pgdata(void)
{
	char	   *pgdata_get_env,
			   *pgdata_set_env;

	if (!pg_data)
	{
		pgdata_get_env = getenv("PGDATA");
		if (pgdata_get_env && strlen(pgdata_get_env))
		{
			/* PGDATA found */
			pg_data = pg_strdup(pgdata_get_env);
		}
		else
		{
			pg_log_error("no data directory specified");
			fprintf(stderr,
					_("You must identify the directory where the data for this database system\n"
					  "will reside.  Do this with either the invocation option -D or the\n"
					  "environment variable PGDATA.\n"));
			exit(1);
		}
	}

	pgdata_native = pg_strdup(pg_data);
	canonicalize_path(pg_data);

	/*
	 * we have to set PGDATA for postgres rather than pass it on the command
	 * line to avoid dumb quoting problems on Windows, and we would especially
	 * need quotes otherwise on Windows because paths there are most likely to
	 * have embedded spaces.
	 */
	pgdata_set_env = psprintf("PGDATA=%s", pg_data);
	putenv(pgdata_set_env);
}