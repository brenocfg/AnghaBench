#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQclientEncoding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  executeCommand (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * executeQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char const* fmtQualifiedId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 int /*<<< orphan*/  pg_log_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splitTableColumnsSpec (char const*,int /*<<< orphan*/ ,char**,char const**) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

void
appendQualifiedRelation(PQExpBuffer buf, const char *spec,
						PGconn *conn, bool echo)
{
	char	   *table;
	const char *columns;
	PQExpBufferData sql;
	PGresult   *res;
	int			ntups;

	splitTableColumnsSpec(spec, PQclientEncoding(conn), &table, &columns);

	/*
	 * Query must remain ABSOLUTELY devoid of unqualified names.  This would
	 * be unnecessary given a regclassin() variant taking a search_path
	 * argument.
	 */
	initPQExpBuffer(&sql);
	appendPQExpBufferStr(&sql,
						 "SELECT c.relname, ns.nspname\n"
						 " FROM pg_catalog.pg_class c,"
						 " pg_catalog.pg_namespace ns\n"
						 " WHERE c.relnamespace OPERATOR(pg_catalog.=) ns.oid\n"
						 "  AND c.oid OPERATOR(pg_catalog.=) ");
	appendStringLiteralConn(&sql, table, conn);
	appendPQExpBufferStr(&sql, "::pg_catalog.regclass;");

	executeCommand(conn, "RESET search_path;", echo);

	/*
	 * One row is a typical result, as is a nonexistent relation ERROR.
	 * regclassin() unconditionally accepts all-digits input as an OID; if no
	 * relation has that OID; this query returns no rows.  Catalog corruption
	 * might elicit other row counts.
	 */
	res = executeQuery(conn, sql.data, echo);
	ntups = PQntuples(res);
	if (ntups != 1)
	{
		pg_log_error(ngettext("query returned %d row instead of one: %s",
							  "query returned %d rows instead of one: %s",
							  ntups),
					 ntups, sql.data);
		PQfinish(conn);
		exit(1);
	}
	appendPQExpBufferStr(buf,
						 fmtQualifiedId(PQgetvalue(res, 0, 1),
										PQgetvalue(res, 0, 0)));
	appendPQExpBufferStr(buf, columns);
	PQclear(res);
	termPQExpBuffer(&sql);
	pg_free(table);

	PQclear(executeQuery(conn, ALWAYS_SECURE_SEARCH_PATH_SQL, echo));
}