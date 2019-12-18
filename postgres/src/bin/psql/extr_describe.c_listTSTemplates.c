#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
struct TYPE_10__ {int translate_header; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_12__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listTSTemplates(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80300)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support full text search.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);

	if (verbose)
		printfPQExpBuffer(&buf,
						  "SELECT\n"
						  "  n.nspname AS \"%s\",\n"
						  "  t.tmplname AS \"%s\",\n"
						  "  t.tmplinit::pg_catalog.regproc AS \"%s\",\n"
						  "  t.tmpllexize::pg_catalog.regproc AS \"%s\",\n"
						  "  pg_catalog.obj_description(t.oid, 'pg_ts_template') AS \"%s\"\n",
						  gettext_noop("Schema"),
						  gettext_noop("Name"),
						  gettext_noop("Init"),
						  gettext_noop("Lexize"),
						  gettext_noop("Description"));
	else
		printfPQExpBuffer(&buf,
						  "SELECT\n"
						  "  n.nspname AS \"%s\",\n"
						  "  t.tmplname AS \"%s\",\n"
						  "  pg_catalog.obj_description(t.oid, 'pg_ts_template') AS \"%s\"\n",
						  gettext_noop("Schema"),
						  gettext_noop("Name"),
						  gettext_noop("Description"));

	appendPQExpBufferStr(&buf, "FROM pg_catalog.pg_ts_template t\n"
						 "LEFT JOIN pg_catalog.pg_namespace n ON n.oid = t.tmplnamespace\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  "n.nspname", "t.tmplname", NULL,
						  "pg_catalog.pg_ts_template_is_visible(t.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of text search templates");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}