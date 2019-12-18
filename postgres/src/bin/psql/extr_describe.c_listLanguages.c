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
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  printACLColumn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listLanguages(const char *pattern, bool verbose, bool showSystem)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT l.lanname AS \"%s\",\n",
					  gettext_noop("Name"));
	if (pset.sversion >= 80300)
		appendPQExpBuffer(&buf,
						  "       pg_catalog.pg_get_userbyid(l.lanowner) as \"%s\",\n",
						  gettext_noop("Owner"));

	appendPQExpBuffer(&buf,
					  "       l.lanpltrusted AS \"%s\"",
					  gettext_noop("Trusted"));

	if (verbose)
	{
		appendPQExpBuffer(&buf,
						  ",\n       NOT l.lanispl AS \"%s\",\n"
						  "       l.lanplcallfoid::pg_catalog.regprocedure AS \"%s\",\n"
						  "       l.lanvalidator::pg_catalog.regprocedure AS \"%s\",\n       ",
						  gettext_noop("Internal language"),
						  gettext_noop("Call handler"),
						  gettext_noop("Validator"));
		if (pset.sversion >= 90000)
			appendPQExpBuffer(&buf, "l.laninline::pg_catalog.regprocedure AS \"%s\",\n       ",
							  gettext_noop("Inline handler"));
		printACLColumn(&buf, "l.lanacl");
	}

	appendPQExpBuffer(&buf,
					  ",\n       d.description AS \"%s\""
					  "\nFROM pg_catalog.pg_language l\n"
					  "LEFT JOIN pg_catalog.pg_description d\n"
					  "  ON d.classoid = l.tableoid AND d.objoid = l.oid\n"
					  "  AND d.objsubid = 0\n",
					  gettext_noop("Description"));

	if (pattern)
		processSQLNamePattern(pset.db, &buf, pattern, false, false,
							  NULL, "l.lanname", NULL, NULL);

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "WHERE l.lanplcallfoid != 0\n");


	appendPQExpBufferStr(&buf, "ORDER BY 1;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of languages");
	myopt.translate_header = true;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}