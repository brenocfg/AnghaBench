#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
struct TYPE_12__ {int translate_header; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_14__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
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
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printACLColumn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
describeTablespaces(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	if (pset.sversion < 80000)
	{
		char		sverbuf[32];

		pg_log_info("The server (version %s) does not support tablespaces.",
					formatPGVersionNumber(pset.sversion, false,
										  sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);

	if (pset.sversion >= 90200)
		printfPQExpBuffer(&buf,
						  "SELECT spcname AS \"%s\",\n"
						  "  pg_catalog.pg_get_userbyid(spcowner) AS \"%s\",\n"
						  "  pg_catalog.pg_tablespace_location(oid) AS \"%s\"",
						  gettext_noop("Name"),
						  gettext_noop("Owner"),
						  gettext_noop("Location"));
	else
		printfPQExpBuffer(&buf,
						  "SELECT spcname AS \"%s\",\n"
						  "  pg_catalog.pg_get_userbyid(spcowner) AS \"%s\",\n"
						  "  spclocation AS \"%s\"",
						  gettext_noop("Name"),
						  gettext_noop("Owner"),
						  gettext_noop("Location"));

	if (verbose)
	{
		appendPQExpBufferStr(&buf, ",\n  ");
		printACLColumn(&buf, "spcacl");
	}

	if (verbose && pset.sversion >= 90000)
		appendPQExpBuffer(&buf,
						  ",\n  spcoptions AS \"%s\"",
						  gettext_noop("Options"));

	if (verbose && pset.sversion >= 90200)
		appendPQExpBuffer(&buf,
						  ",\n  pg_catalog.pg_size_pretty(pg_catalog.pg_tablespace_size(oid)) AS \"%s\"",
						  gettext_noop("Size"));

	if (verbose && pset.sversion >= 80200)
		appendPQExpBuffer(&buf,
						  ",\n  pg_catalog.shobj_description(oid, 'pg_tablespace') AS \"%s\"",
						  gettext_noop("Description"));

	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_tablespace\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL, "spcname", NULL,
						  NULL);

	appendPQExpBufferStr(&buf, "ORDER BY 1;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of tablespaces");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}