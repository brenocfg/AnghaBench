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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  OPF ; 
 int /*<<< orphan*/  PG_BINARY_A ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  database_exclude_names ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit_nicely (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 char* filename ; 
 int /*<<< orphan*/  fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ output_clean ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,char*) ; 
 int runPgDump (char*,char const*) ; 
 scalar_t__ simple_string_list_member (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
dumpDatabases(PGconn *conn)
{
	PGresult   *res;
	int			i;

	/*
	 * Skip databases marked not datallowconn, since we'd be unable to connect
	 * to them anyway.  This must agree with dropDBs().
	 *
	 * We arrange for template1 to be processed first, then we process other
	 * DBs in alphabetical order.  If we just did them all alphabetically, we
	 * might find ourselves trying to drop the "postgres" database while still
	 * connected to it.  This makes trying to run the restore script while
	 * connected to "template1" a bad idea, but there's no fixed order that
	 * doesn't have some failure mode with --clean.
	 */
	res = executeQuery(conn,
					   "SELECT datname "
					   "FROM pg_database d "
					   "WHERE datallowconn "
					   "ORDER BY (datname <> 'template1'), datname");

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Databases\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *dbname = PQgetvalue(res, i, 0);
		const char *create_opts;
		int			ret;

		/* Skip template0, even if it's not marked !datallowconn. */
		if (strcmp(dbname, "template0") == 0)
			continue;

		/* Skip any explicitly excluded database */
		if (simple_string_list_member(&database_exclude_names, dbname))
		{
			pg_log_info("excluding database \"%s\"", dbname);
			continue;
		}

		pg_log_info("dumping database \"%s\"", dbname);

		fprintf(OPF, "--\n-- Database \"%s\" dump\n--\n\n", dbname);

		/*
		 * We assume that "template1" and "postgres" already exist in the
		 * target installation.  dropDBs() won't have removed them, for fear
		 * of removing the DB the restore script is initially connected to. If
		 * --clean was specified, tell pg_dump to drop and recreate them;
		 * otherwise we'll merely restore their contents.  Other databases
		 * should simply be created.
		 */
		if (strcmp(dbname, "template1") == 0 || strcmp(dbname, "postgres") == 0)
		{
			if (output_clean)
				create_opts = "--clean --create";
			else
			{
				create_opts = "";
				/* Since pg_dump won't emit a \connect command, we must */
				fprintf(OPF, "\\connect %s\n\n", dbname);
			}
		}
		else
			create_opts = "--create";

		if (filename)
			fclose(OPF);

		ret = runPgDump(dbname, create_opts);
		if (ret != 0)
		{
			pg_log_error("pg_dump failed on database \"%s\", exiting", dbname);
			exit_nicely(1);
		}

		if (filename)
		{
			OPF = fopen(filename, PG_BINARY_A);
			if (!OPF)
			{
				pg_log_error("could not re-open the output file \"%s\": %m",
							 filename);
				exit_nicely(1);
			}
		}

	}

	PQclear(res);
}