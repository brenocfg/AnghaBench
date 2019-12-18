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
struct TYPE_7__ {char* data; } ;
typedef  int ReindexType ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (char const*) ; 
 int /*<<< orphan*/  PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int PQsendQuery (int /*<<< orphan*/ *,char*) ; 
#define  REINDEX_DATABASE 132 
#define  REINDEX_INDEX 131 
#define  REINDEX_SCHEMA 130 
#define  REINDEX_SYSTEM 129 
#define  REINDEX_TABLE 128 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendQualifiedRelation (TYPE_1__*,char const*,int /*<<< orphan*/ *,int) ; 
 int executeMaintenanceCommand (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char const* fmtId (char const*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
run_reindex_command(PGconn *conn, ReindexType type, const char *name,
					bool echo, bool verbose, bool concurrently, bool async)
{
	PQExpBufferData sql;
	bool		status;

	Assert(name);

	/* build the REINDEX query */
	initPQExpBuffer(&sql);

	appendPQExpBufferStr(&sql, "REINDEX ");

	if (verbose)
		appendPQExpBufferStr(&sql, "(VERBOSE) ");

	/* object type */
	switch (type)
	{
		case REINDEX_DATABASE:
			appendPQExpBufferStr(&sql, "DATABASE ");
			break;
		case REINDEX_INDEX:
			appendPQExpBufferStr(&sql, "INDEX ");
			break;
		case REINDEX_SCHEMA:
			appendPQExpBufferStr(&sql, "SCHEMA ");
			break;
		case REINDEX_SYSTEM:
			appendPQExpBufferStr(&sql, "SYSTEM ");
			break;
		case REINDEX_TABLE:
			appendPQExpBufferStr(&sql, "TABLE ");
			break;
	}

	if (concurrently)
		appendPQExpBufferStr(&sql, "CONCURRENTLY ");

	/* object name */
	switch (type)
	{
		case REINDEX_DATABASE:
		case REINDEX_SYSTEM:
			appendPQExpBufferStr(&sql, fmtId(name));
			break;
		case REINDEX_INDEX:
		case REINDEX_TABLE:
			appendQualifiedRelation(&sql, name, conn, echo);
			break;
		case REINDEX_SCHEMA:
			appendPQExpBufferStr(&sql, name);
			break;
	}

	/* finish the query */
	appendPQExpBufferChar(&sql, ';');

	if (async)
	{
		if (echo)
			printf("%s\n", sql.data);

		status = PQsendQuery(conn, sql.data) == 1;
	}
	else
		status = executeMaintenanceCommand(conn, sql.data, echo);

	if (!status)
	{
		switch (type)
		{
			case REINDEX_DATABASE:
				pg_log_error("reindexing of database \"%s\" failed: %s",
							 PQdb(conn), PQerrorMessage(conn));
				break;
			case REINDEX_INDEX:
				pg_log_error("reindexing of index \"%s\" in database \"%s\" failed: %s",
							 name, PQdb(conn), PQerrorMessage(conn));
				break;
			case REINDEX_SCHEMA:
				pg_log_error("reindexing of schema \"%s\" in database \"%s\" failed: %s",
							 name, PQdb(conn), PQerrorMessage(conn));
				break;
			case REINDEX_SYSTEM:
				pg_log_error("reindexing of system catalogs on database \"%s\" failed: %s",
							 PQdb(conn), PQerrorMessage(conn));
				break;
			case REINDEX_TABLE:
				pg_log_error("reindexing of table \"%s\" in database \"%s\" failed: %s",
							 name, PQdb(conn), PQerrorMessage(conn));
				break;
		}
		if (!async)
		{
			PQfinish(conn);
			exit(1);
		}
	}

	termPQExpBuffer(&sql);
}