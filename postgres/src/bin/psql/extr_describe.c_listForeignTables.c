#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
struct TYPE_11__ {int translate_header; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_13__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listForeignTables(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 90100)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support foreign tables.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);
	printfPQExpBuffer(&buf,
					  "SELECT n.nspname AS \"%s\",\n"
					  "  c.relname AS \"%s\",\n"
					  "  s.srvname AS \"%s\"",
					  gettext_noop("Schema"),
					  gettext_noop("Table"),
					  gettext_noop("Server"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n CASE WHEN ftoptions IS NULL THEN '' ELSE "
						  "  '(' || pg_catalog.array_to_string(ARRAY(SELECT "
						  "  pg_catalog.quote_ident(option_name) ||  ' ' || "
						  "  pg_catalog.quote_literal(option_value)  FROM "
						  "  pg_catalog.pg_options_to_table(ftoptions)),  ', ') || ')' "
						  "  END AS \"%s\",\n"
						  "  d.description AS \"%s\"",
						  gettext_noop("FDW options"),
						  gettext_noop("Description"));

	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_foreign_table ft\n"
						 "  INNER JOIN pg_catalog.pg_class c"
						 " ON c.oid = ft.ftrelid\n"
						 "  INNER JOIN pg_catalog.pg_namespace n"
						 " ON n.oid = c.relnamespace\n"
						 "  INNER JOIN pg_catalog.pg_foreign_server s"
						 " ON s.oid = ft.ftserver\n");
	if (verbose)
		appendPQExpBufferStr(&buf,
							 "   LEFT JOIN pg_catalog.pg_description d\n"
							 "          ON d.classoid = c.tableoid AND "
							 "d.objoid = c.oid AND d.objsubid = 0\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  "n.nspname", "c.relname", NULL,
						  "pg_catalog.pg_table_is_visible(c.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of foreign tables");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}