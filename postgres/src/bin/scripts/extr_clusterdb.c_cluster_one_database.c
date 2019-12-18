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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendQualifiedRelation (TYPE_1__*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * connectDatabase (char const*,char const*,char const*,char const*,int,char const*,int,int,int) ; 
 int /*<<< orphan*/  executeMaintenanceCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
cluster_one_database(const char *dbname, bool verbose, const char *table,
					 const char *host, const char *port,
					 const char *username, enum trivalue prompt_password,
					 const char *progname, bool echo)
{
	PQExpBufferData sql;

	PGconn	   *conn;

	conn = connectDatabase(dbname, host, port, username, prompt_password,
						   progname, echo, false, false);

	initPQExpBuffer(&sql);

	appendPQExpBufferStr(&sql, "CLUSTER");
	if (verbose)
		appendPQExpBufferStr(&sql, " VERBOSE");
	if (table)
	{
		appendPQExpBufferChar(&sql, ' ');
		appendQualifiedRelation(&sql, table, conn, echo);
	}
	appendPQExpBufferChar(&sql, ';');

	if (!executeMaintenanceCommand(conn, sql.data, echo))
	{
		if (table)
			pg_log_error("clustering of table \"%s\" in database \"%s\" failed: %s",
						 table, PQdb(conn), PQerrorMessage(conn));
		else
			pg_log_error("clustering of database \"%s\" failed: %s",
						 PQdb(conn), PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}
	PQfinish(conn);
	termPQExpBuffer(&sql);
}