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
struct TYPE_12__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  quiet; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
listDbRoleSettings(const char *pattern, const char *pattern2)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	bool		havewhere;

	if (pset.sversion < 90000)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support per-database role settings.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf, "SELECT rolname AS \"%s\", datname AS \"%s\",\n"
					  "pg_catalog.array_to_string(setconfig, E'\\n') AS \"%s\"\n"
					  "FROM pg_catalog.pg_db_role_setting s\n"
					  "LEFT JOIN pg_catalog.pg_database d ON d.oid = setdatabase\n"
					  "LEFT JOIN pg_catalog.pg_roles r ON r.oid = setrole\n",
					  gettext_noop("Role"),
					  gettext_noop("Database"),
					  gettext_noop("Settings"));
	havewhere = processSQLNamePattern(pset.db, &buf, pattern, false, false,
									  NULL, "r.rolname", NULL, NULL);
	processSQLNamePattern(pset.db, &buf, pattern2, havewhere, false,
						  NULL, "d.datname", NULL, NULL);
	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	/*
	 * Most functions in this file are content to print an empty table when
	 * there are no matching objects.  We intentionally deviate from that
	 * here, but only in !quiet mode, because of the possibility that the user
	 * is confused about what the two pattern arguments mean.
	 */
	if (PQntuples(res) == 0 && !pset.quiet)
	{
		if (pattern && pattern2)
			pg_log_error("Did not find any settings for role \"%s\" and database \"%s\".",
						 pattern, pattern2);
		else if (pattern)
			pg_log_error("Did not find any settings for role \"%s\".",
						 pattern);
		else
			pg_log_error("Did not find any settings.");
	}
	else
	{
		myopt.nullPrint = NULL;
		myopt.title = _("List of settings");
		myopt.translate_header = true;

		printQuery(res, &myopt, pset.queryFout, false, pset.logfile);
	}

	PQclear(res);
	return true;
}