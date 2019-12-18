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
struct TYPE_11__ {int translate_header; int const* translate_columns; int /*<<< orphan*/  n_translate_columns; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_13__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  lengthof (int const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listCollations(const char *pattern, bool verbose, bool showSystem)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, false, false, false, true, false};

	if (pset.sversion < 90100)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support collations.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT n.nspname AS \"%s\",\n"
					  "       c.collname AS \"%s\",\n"
					  "       c.collcollate AS \"%s\",\n"
					  "       c.collctype AS \"%s\"",
					  gettext_noop("Schema"),
					  gettext_noop("Name"),
					  gettext_noop("Collate"),
					  gettext_noop("Ctype"));

	if (pset.sversion >= 100000)
		appendPQExpBuffer(&buf,
						  ",\n       CASE c.collprovider WHEN 'd' THEN 'default' WHEN 'c' THEN 'libc' WHEN 'i' THEN 'icu' END AS \"%s\"",
						  gettext_noop("Provider"));
	else
		appendPQExpBuffer(&buf,
						  ",\n       'libc' AS \"%s\"",
						  gettext_noop("Provider"));

	if (pset.sversion >= 120000)
		appendPQExpBuffer(&buf,
						  ",\n       CASE WHEN c.collisdeterministic THEN '%s' ELSE '%s' END AS \"%s\"",
						  gettext_noop("yes"), gettext_noop("no"),
						  gettext_noop("Deterministic?"));
	else
		appendPQExpBuffer(&buf,
						  ",\n       '%s' AS \"%s\"",
						  gettext_noop("yes"),
						  gettext_noop("Deterministic?"));

	if (verbose)
		appendPQExpBuffer(&buf,
						  ",\n       pg_catalog.obj_description(c.oid, 'pg_collation') AS \"%s\"",
						  gettext_noop("Description"));

	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_collation c, pg_catalog.pg_namespace n\n"
						 "WHERE n.oid = c.collnamespace\n");

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "      AND n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	/*
	 * Hide collations that aren't usable in the current database's encoding.
	 * If you think to change this, note that pg_collation_is_visible rejects
	 * unusable collations, so you will need to hack name pattern processing
	 * somehow to avoid inconsistent behavior.
	 */
	appendPQExpBufferStr(&buf, "      AND c.collencoding IN (-1, pg_catalog.pg_char_to_encoding(pg_catalog.getdatabaseencoding()))\n");

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "c.collname", NULL,
						  "pg_catalog.pg_collation_is_visible(c.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of collations");
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}