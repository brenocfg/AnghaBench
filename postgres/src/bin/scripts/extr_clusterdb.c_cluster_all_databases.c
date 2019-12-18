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
typedef  enum trivalue { ____Placeholder_trivalue } trivalue ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cluster_one_database (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char const*,char const*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/ * connectMaintenanceDatabase (char const*,char const*,char const*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
cluster_all_databases(bool verbose, const char *maintenance_db,
					  const char *host, const char *port,
					  const char *username, enum trivalue prompt_password,
					  const char *progname, bool echo, bool quiet)
{
	PGconn	   *conn;
	PGresult   *result;
	PQExpBufferData connstr;
	int			i;

	conn = connectMaintenanceDatabase(maintenance_db, host, port, username,
									  prompt_password, progname, echo);
	result = executeQuery(conn, "SELECT datname FROM pg_database WHERE datallowconn ORDER BY 1;", echo);
	PQfinish(conn);

	initPQExpBuffer(&connstr);
	for (i = 0; i < PQntuples(result); i++)
	{
		char	   *dbname = PQgetvalue(result, i, 0);

		if (!quiet)
		{
			printf(_("%s: clustering database \"%s\"\n"), progname, dbname);
			fflush(stdout);
		}

		resetPQExpBuffer(&connstr);
		appendPQExpBufferStr(&connstr, "dbname=");
		appendConnStrVal(&connstr, dbname);

		cluster_one_database(connstr.data, verbose, NULL,
							 host, port, username, prompt_password,
							 progname, echo);
	}
	termPQExpBuffer(&connstr);

	PQclear(result);
}