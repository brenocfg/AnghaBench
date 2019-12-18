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
struct TYPE_11__ {int translate_header; int const* translate_columns; int /*<<< orphan*/  n_translate_columns; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_13__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  COERCION_CODE_ASSIGNMENT ; 
 int /*<<< orphan*/  COERCION_CODE_EXPLICIT ; 
 int /*<<< orphan*/  COERCION_METHOD_BINARY ; 
 int /*<<< orphan*/  COERCION_METHOD_INOUT ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  lengthof (int const*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,char*,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listCasts(const char *pattern, bool verbose)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, false, true, false};

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT pg_catalog.format_type(castsource, NULL) AS \"%s\",\n"
					  "       pg_catalog.format_type(casttarget, NULL) AS \"%s\",\n",
					  gettext_noop("Source type"),
					  gettext_noop("Target type"));

	/*
	 * We don't attempt to localize '(binary coercible)' or '(with inout)',
	 * because there's too much risk of gettext translating a function name
	 * that happens to match some string in the PO database.
	 */
	if (pset.sversion >= 80400)
		appendPQExpBuffer(&buf,
						  "       CASE WHEN c.castmethod = '%c' THEN '(binary coercible)'\n"
						  "            WHEN c.castmethod = '%c' THEN '(with inout)'\n"
						  "            ELSE p.proname\n"
						  "       END AS \"%s\",\n",
						  COERCION_METHOD_BINARY,
						  COERCION_METHOD_INOUT,
						  gettext_noop("Function"));
	else
		appendPQExpBuffer(&buf,
						  "       CASE WHEN c.castfunc = 0 THEN '(binary coercible)'\n"
						  "            ELSE p.proname\n"
						  "       END AS \"%s\",\n",
						  gettext_noop("Function"));

	appendPQExpBuffer(&buf,
					  "       CASE WHEN c.castcontext = '%c' THEN '%s'\n"
					  "            WHEN c.castcontext = '%c' THEN '%s'\n"
					  "            ELSE '%s'\n"
					  "       END AS \"%s\"",
					  COERCION_CODE_EXPLICIT,
					  gettext_noop("no"),
					  COERCION_CODE_ASSIGNMENT,
					  gettext_noop("in assignment"),
					  gettext_noop("yes"),
					  gettext_noop("Implicit?"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n       d.description AS \"%s\"",
						  gettext_noop("Description"));

	/*
	 * We need a left join to pg_proc for binary casts; the others are just
	 * paranoia.
	 */
	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_cast c LEFT JOIN pg_catalog.pg_proc p\n"
						 "     ON c.castfunc = p.oid\n"
						 "     LEFT JOIN pg_catalog.pg_type ts\n"
						 "     ON c.castsource = ts.oid\n"
						 "     LEFT JOIN pg_catalog.pg_namespace ns\n"
						 "     ON ns.oid = ts.typnamespace\n"
						 "     LEFT JOIN pg_catalog.pg_type tt\n"
						 "     ON c.casttarget = tt.oid\n"
						 "     LEFT JOIN pg_catalog.pg_namespace nt\n"
						 "     ON nt.oid = tt.typnamespace\n");

	if (verbose)
		appendPQExpBufferStr(&buf,
							 "     LEFT JOIN pg_catalog.pg_description d\n"
							 "     ON d.classoid = c.tableoid AND d.objoid = "
							 "c.oid AND d.objsubid = 0\n");

	appendPQExpBufferStr(&buf, "WHERE ( (true");

	/*
	 * Match name pattern against either internal or external name of either
	 * castsource or casttarget
	 */
	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "ns.nspname", "ts.typname",
						  "pg_catalog.format_type(ts.oid, NULL)",
						  "pg_catalog.pg_type_is_visible(ts.oid)");

	appendPQExpBufferStr(&buf, ") OR (true");

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "nt.nspname", "tt.typname",
						  "pg_catalog.format_type(tt.oid, NULL)",
						  "pg_catalog.pg_type_is_visible(tt.oid)");

	appendPQExpBufferStr(&buf, ") )\nORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of casts");
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}