#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
typedef  int /*<<< orphan*/  printTableOpt ;
typedef  int /*<<< orphan*/  printTableContent ;
struct TYPE_9__ {int /*<<< orphan*/  topt; } ;
struct TYPE_11__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; TYPE_1__ popt; int /*<<< orphan*/  quiet; int /*<<< orphan*/  db; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printTableAddCell (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  printTableAddFooter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printTableAddHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const) ; 
 int /*<<< orphan*/  printTableCleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printTableInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ pset ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
describePublications(const char *pattern)
{
	PQExpBufferData buf;
	int			i;
	PGresult   *res;
	bool		has_pubtruncate;

	if (pset.sversion < 100000)
	{
		char		sverbuf[32];

		pg_log_error("The server (version %s) does not support publications.",
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	has_pubtruncate = (pset.sversion >= 110000);

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT oid, pubname,\n"
					  "  pg_catalog.pg_get_userbyid(pubowner) AS owner,\n"
					  "  puballtables, pubinsert, pubupdate, pubdelete");
	if (has_pubtruncate)
		appendPQExpBufferStr(&buf,
							 ", pubtruncate");
	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_publication\n");

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  NULL, "pubname", NULL,
						  NULL);

	appendPQExpBufferStr(&buf, "ORDER BY 2;");

	res = PSQLexec(buf.data);
	if (!res)
	{
		termPQExpBuffer(&buf);
		return false;
	}

	if (PQntuples(res) == 0)
	{
		if (!pset.quiet)
		{
			if (pattern)
				pg_log_error("Did not find any publication named \"%s\".",
							 pattern);
			else
				pg_log_error("Did not find any publications.");
		}

		termPQExpBuffer(&buf);
		PQclear(res);
		return false;
	}

	for (i = 0; i < PQntuples(res); i++)
	{
		const char	align = 'l';
		int			ncols = 5;
		int			nrows = 1;
		int			tables = 0;
		PGresult   *tabres;
		char	   *pubid = PQgetvalue(res, i, 0);
		char	   *pubname = PQgetvalue(res, i, 1);
		bool		puballtables = strcmp(PQgetvalue(res, i, 3), "t") == 0;
		int			j;
		PQExpBufferData title;
		printTableOpt myopt = pset.popt.topt;
		printTableContent cont;

		if (has_pubtruncate)
			ncols++;

		initPQExpBuffer(&title);
		printfPQExpBuffer(&title, _("Publication %s"), pubname);
		printTableInit(&cont, &myopt, title.data, ncols, nrows);

		printTableAddHeader(&cont, gettext_noop("Owner"), true, align);
		printTableAddHeader(&cont, gettext_noop("All tables"), true, align);
		printTableAddHeader(&cont, gettext_noop("Inserts"), true, align);
		printTableAddHeader(&cont, gettext_noop("Updates"), true, align);
		printTableAddHeader(&cont, gettext_noop("Deletes"), true, align);
		if (has_pubtruncate)
			printTableAddHeader(&cont, gettext_noop("Truncates"), true, align);

		printTableAddCell(&cont, PQgetvalue(res, i, 2), false, false);
		printTableAddCell(&cont, PQgetvalue(res, i, 3), false, false);
		printTableAddCell(&cont, PQgetvalue(res, i, 4), false, false);
		printTableAddCell(&cont, PQgetvalue(res, i, 5), false, false);
		printTableAddCell(&cont, PQgetvalue(res, i, 6), false, false);
		if (has_pubtruncate)
			printTableAddCell(&cont, PQgetvalue(res, i, 7), false, false);

		if (!puballtables)
		{
			printfPQExpBuffer(&buf,
							  "SELECT n.nspname, c.relname\n"
							  "FROM pg_catalog.pg_class c,\n"
							  "     pg_catalog.pg_namespace n,\n"
							  "     pg_catalog.pg_publication_rel pr\n"
							  "WHERE c.relnamespace = n.oid\n"
							  "  AND c.oid = pr.prrelid\n"
							  "  AND pr.prpubid = '%s'\n"
							  "ORDER BY 1,2", pubid);

			tabres = PSQLexec(buf.data);
			if (!tabres)
			{
				printTableCleanup(&cont);
				PQclear(res);
				termPQExpBuffer(&buf);
				termPQExpBuffer(&title);
				return false;
			}
			else
				tables = PQntuples(tabres);

			if (tables > 0)
				printTableAddFooter(&cont, _("Tables:"));

			for (j = 0; j < tables; j++)
			{
				printfPQExpBuffer(&buf, "    \"%s.%s\"",
								  PQgetvalue(tabres, j, 0),
								  PQgetvalue(tabres, j, 1));

				printTableAddFooter(&cont, buf.data);
			}
			PQclear(tabres);
		}

		printTable(&cont, pset.queryFout, false, pset.logfile);
		printTableCleanup(&cont);

		termPQExpBuffer(&title);
	}

	termPQExpBuffer(&buf);
	PQclear(res);

	return true;
}