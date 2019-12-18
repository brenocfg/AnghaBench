#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  quiet; int /*<<< orphan*/  db; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  describeOneTSParser (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_1__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static bool
listTSParsersVerbose(const char *pattern)
{
	PQExpBufferData buf;
	PGresult   *res;
	int			i;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT p.oid,\n"
					  "  n.nspname,\n"
					  "  p.prsname\n"
					  "FROM pg_catalog.pg_ts_parser p\n"
					  "LEFT JOIN pg_catalog.pg_namespace n ON n.oid = p.prsnamespace\n"
		);

	processSQLNamePattern(pset.db, &buf, pattern, false, false,
						  "n.nspname", "p.prsname", NULL,
						  "pg_catalog.pg_ts_parser_is_visible(p.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	if (PQntuples(res) == 0)
	{
		if (!pset.quiet)
		{
			if (pattern)
				pg_log_error("Did not find any text search parser named \"%s\".",
							 pattern);
			else
				pg_log_error("Did not find any text search parsers.");
		}
		PQclear(res);
		return false;
	}

	for (i = 0; i < PQntuples(res); i++)
	{
		const char *oid;
		const char *nspname = NULL;
		const char *prsname;

		oid = PQgetvalue(res, i, 0);
		if (!PQgetisnull(res, i, 1))
			nspname = PQgetvalue(res, i, 1);
		prsname = PQgetvalue(res, i, 2);

		if (!describeOneTSParser(oid, nspname, prsname))
		{
			PQclear(res);
			return false;
		}

		if (cancel_pressed)
		{
			PQclear(res);
			return false;
		}
	}

	PQclear(res);
	return true;
}