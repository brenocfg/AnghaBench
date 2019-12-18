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
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  describeOneTableDetails (char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_1__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

bool
describeTableDetails(const char *pattern, bool verbose, bool showSystem)
{
	PQExpBufferData buf;
	PGresult   *res;
	int			i;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT c.oid,\n"
					  "  n.nspname,\n"
					  "  c.relname\n"
					  "FROM pg_catalog.pg_class c\n"
					  "     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace\n");

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "WHERE n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	processSQLNamePattern(pset.db, &buf, pattern, !showSystem && !pattern, false,
						  "n.nspname", "c.relname", NULL,
						  "pg_catalog.pg_table_is_visible(c.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 2, 3;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	if (PQntuples(res) == 0)
	{
		if (!pset.quiet)
		{
			if (pattern)
				pg_log_error("Did not find any relation named \"%s\".",
							 pattern);
			else
				pg_log_error("Did not find any relations.");
		}
		PQclear(res);
		return false;
	}

	for (i = 0; i < PQntuples(res); i++)
	{
		const char *oid;
		const char *nspname;
		const char *relname;

		oid = PQgetvalue(res, i, 0);
		nspname = PQgetvalue(res, i, 1);
		relname = PQgetvalue(res, i, 2);

		if (!describeOneTableDetails(nspname, relname, oid, verbose))
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