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
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fmtId (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ if_exists ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
dropDBs(PGconn *conn)
{
	PGresult   *res;
	int			i;

	/*
	 * Skip databases marked not datallowconn, since we'd be unable to connect
	 * to them anyway.  This must agree with dumpDatabases().
	 */
	res = executeQuery(conn,
					   "SELECT datname "
					   "FROM pg_database d "
					   "WHERE datallowconn "
					   "ORDER BY datname");

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Drop databases (except postgres and template1)\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *dbname = PQgetvalue(res, i, 0);

		/*
		 * Skip "postgres" and "template1"; dumpDatabases() will deal with
		 * them specially.  Also, be sure to skip "template0", even if for
		 * some reason it's not marked !datallowconn.
		 */
		if (strcmp(dbname, "template1") != 0 &&
			strcmp(dbname, "template0") != 0 &&
			strcmp(dbname, "postgres") != 0)
		{
			fprintf(OPF, "DROP DATABASE %s%s;\n",
					if_exists ? "IF EXISTS " : "",
					fmtId(dbname));
		}
	}

	PQclear(res);

	fprintf(OPF, "\n\n");
}