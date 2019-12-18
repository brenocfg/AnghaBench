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
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 scalar_t__ CONNECTION_OK ; 
 int /*<<< orphan*/  PG_REPORT ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  executeQueryOrDie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * get_db_conn (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

PGconn *
connectToServer(ClusterInfo *cluster, const char *db_name)
{
	PGconn	   *conn = get_db_conn(cluster, db_name);

	if (conn == NULL || PQstatus(conn) != CONNECTION_OK)
	{
		pg_log(PG_REPORT, "connection to database failed: %s",
			   PQerrorMessage(conn));

		if (conn)
			PQfinish(conn);

		printf(_("Failure, exiting\n"));
		exit(1);
	}

	PQclear(executeQueryOrDie(conn, ALWAYS_SECURE_SEARCH_PATH_SQL));

	return conn;
}