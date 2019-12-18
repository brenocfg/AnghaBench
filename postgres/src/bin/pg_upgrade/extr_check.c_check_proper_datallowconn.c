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
typedef  int /*<<< orphan*/  ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/ * connectToServer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * executeQueryOrDie (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 
 int /*<<< orphan*/  prep_status (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
check_proper_datallowconn(ClusterInfo *cluster)
{
	int			dbnum;
	PGconn	   *conn_template1;
	PGresult   *dbres;
	int			ntups;
	int			i_datname;
	int			i_datallowconn;

	prep_status("Checking database connection settings");

	conn_template1 = connectToServer(cluster, "template1");

	/* get database names */
	dbres = executeQueryOrDie(conn_template1,
							  "SELECT	datname, datallowconn "
							  "FROM	pg_catalog.pg_database");

	i_datname = PQfnumber(dbres, "datname");
	i_datallowconn = PQfnumber(dbres, "datallowconn");

	ntups = PQntuples(dbres);
	for (dbnum = 0; dbnum < ntups; dbnum++)
	{
		char	   *datname = PQgetvalue(dbres, dbnum, i_datname);
		char	   *datallowconn = PQgetvalue(dbres, dbnum, i_datallowconn);

		if (strcmp(datname, "template0") == 0)
		{
			/* avoid restore failure when pg_dumpall tries to create template0 */
			if (strcmp(datallowconn, "t") == 0)
				pg_fatal("template0 must not allow connections, "
						 "i.e. its pg_database.datallowconn must be false\n");
		}
		else
		{
			/*
			 * avoid datallowconn == false databases from being skipped on
			 * restore
			 */
			if (strcmp(datallowconn, "f") == 0)
				pg_fatal("All non-template0 databases must allow connections, "
						 "i.e. their pg_database.datallowconn must be true\n");
		}
	}

	PQclear(dbres);

	PQfinish(conn_template1);

	check_ok();
}