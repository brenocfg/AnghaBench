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
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listUserMappings(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80400)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support user mappings.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);
	printfPQExpBuffer(&buf,
					  "SELECT um.srvname AS \"%s\",\n"
					  "  um.usename AS \"%s\"",
					  gettext_noop("Server"),
					  gettext_noop("User name"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n CASE WHEN umoptions IS NULL THEN '' ELSE "
						  "  '(' || pg_catalog.array_to_string(ARRAY(SELECT "
						  "  pg_catalog.quote_ident(option_name) ||  ' ' || "
						  "  pg_catalog.quote_literal(option_value)  FROM "
						  "  pg_catalog.pg_options_to_table(umoptions)),  ', ') || ')' "
						  "  END AS \"%s\"",
						  gettext_noop("FDW options"));

	appendPQExpBufferStr(&buf, "\nFROM pg_catalog.pg_user_mappings um\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL, "um.srvname", "um.usename", NULL);

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of user mappings");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}