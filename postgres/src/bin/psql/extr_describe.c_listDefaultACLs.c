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
 int /*<<< orphan*/  DEFACLOBJ_FUNCTION ; 
 int /*<<< orphan*/  DEFACLOBJ_NAMESPACE ; 
 int /*<<< orphan*/  DEFACLOBJ_RELATION ; 
 int /*<<< orphan*/  DEFACLOBJ_SEQUENCE ; 
 int /*<<< orphan*/  DEFACLOBJ_TYPE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  lengthof (int const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printACLColumn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listDefaultACLs(const char *pattern)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, true, false};

	if (pset.sversion < 90000)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support altering default privileges.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT pg_catalog.pg_get_userbyid(d.defaclrole) AS \"%s\",\n"
					  "  n.nspname AS \"%s\",\n"
					  "  CASE d.defaclobjtype WHEN '%c' THEN '%s' WHEN '%c' THEN '%s' WHEN '%c' THEN '%s' WHEN '%c' THEN '%s' WHEN '%c' THEN '%s' END AS \"%s\",\n"
					  "  ",
					  gettext_noop("Owner"),
					  gettext_noop("Schema"),
					  DEFACLOBJ_RELATION,
					  gettext_noop("table"),
					  DEFACLOBJ_SEQUENCE,
					  gettext_noop("sequence"),
					  DEFACLOBJ_FUNCTION,
					  gettext_noop("function"),
					  DEFACLOBJ_TYPE,
					  gettext_noop("type"),
					  DEFACLOBJ_NAMESPACE,
					  gettext_noop("schema"),
					  gettext_noop("Type"));

	printACLColumn(&buf, "d.defaclacl");

	appendPQExpBufferStr(&buf, "\nFROM pg_catalog.pg_default_acl d\n"
						 "     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = d.defaclnamespace\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL,
						  "n.nspname",
						  "pg_catalog.pg_get_userbyid(d.defaclrole)",
						  NULL);

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2, 3;");

	res = PSQLexec(buf.data);
	if (!res)
	{
		termPQExpBuffer(&buf);
		return false;
	}

	myopt.nullPrint = NULL;
	printfPQExpBuffer(&buf, _("Default access privileges"));
	myopt.title = buf.data;
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	termPQExpBuffer(&buf);
	PQclear(res);
	return true;
}