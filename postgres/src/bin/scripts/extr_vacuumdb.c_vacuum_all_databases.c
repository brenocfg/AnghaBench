#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vacuumingOptions ;
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int ANALYZE_NO_STAGE ; 
 int ANALYZE_NUM_STAGES ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * connectMaintenanceDatabase (char const*,char const*,char const*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  vacuum_one_database (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,char const*,char const*,int,int,char const*,int,int) ; 

__attribute__((used)) static void
vacuum_all_databases(vacuumingOptions *vacopts,
					 bool analyze_in_stages,
					 const char *maintenance_db, const char *host,
					 const char *port, const char *username,
					 enum trivalue prompt_password,
					 int concurrentCons,
					 const char *progname, bool echo, bool quiet)
{
	PGconn	   *conn;
	PGresult   *result;
	PQExpBufferData connstr;
	int			stage;
	int			i;

	conn = connectMaintenanceDatabase(maintenance_db, host, port, username,
									  prompt_password, progname, echo);
	result = executeQuery(conn,
						  "SELECT datname FROM pg_database WHERE datallowconn ORDER BY 1;",
						  echo);
	PQfinish(conn);

	initPQExpBuffer(&connstr);
	if (analyze_in_stages)
	{
		/*
		 * When analyzing all databases in stages, we analyze them all in the
		 * fastest stage first, so that initial statistics become available
		 * for all of them as soon as possible.
		 *
		 * This means we establish several times as many connections, but
		 * that's a secondary consideration.
		 */
		for (stage = 0; stage < ANALYZE_NUM_STAGES; stage++)
		{
			for (i = 0; i < PQntuples(result); i++)
			{
				resetPQExpBuffer(&connstr);
				appendPQExpBufferStr(&connstr, "dbname=");
				appendConnStrVal(&connstr, PQgetvalue(result, i, 0));

				vacuum_one_database(connstr.data, vacopts,
									stage,
									NULL,
									host, port, username, prompt_password,
									concurrentCons,
									progname, echo, quiet);
			}
		}
	}
	else
	{
		for (i = 0; i < PQntuples(result); i++)
		{
			resetPQExpBuffer(&connstr);
			appendPQExpBufferStr(&connstr, "dbname=");
			appendConnStrVal(&connstr, PQgetvalue(result, i, 0));

			vacuum_one_database(connstr.data, vacopts,
								ANALYZE_NO_STAGE,
								NULL,
								host, port, username, prompt_password,
								concurrentCons,
								progname, echo, quiet);
		}
	}
	termPQExpBuffer(&connstr);

	PQclear(result);
}