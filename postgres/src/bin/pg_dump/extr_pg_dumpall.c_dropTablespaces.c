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

__attribute__((used)) static void
dropTablespaces(PGconn *conn)
{
	PGresult   *res;
	int			i;

	/*
	 * Get all tablespaces except built-in ones (which we assume are named
	 * pg_xxx)
	 */
	res = executeQuery(conn, "SELECT spcname "
					   "FROM pg_catalog.pg_tablespace "
					   "WHERE spcname !~ '^pg_' "
					   "ORDER BY 1");

	if (PQntuples(res) > 0)
		fprintf(OPF, "--\n-- Drop tablespaces\n--\n\n");

	for (i = 0; i < PQntuples(res); i++)
	{
		char	   *spcname = PQgetvalue(res, i, 0);

		fprintf(OPF, "DROP TABLESPACE %s%s;\n",
				if_exists ? "IF EXISTS " : "",
				fmtId(spcname));
	}

	PQclear(res);

	fprintf(OPF, "\n\n");
}