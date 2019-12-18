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
 int /*<<< orphan*/  describeOneTSConfig (char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_1__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static bool
listTSConfigsVerbose(const char *pattern)
{
	PQExpBufferData buf;
	PGresult   *res;
	int			i;

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT c.oid, c.cfgname,\n"
					  "   n.nspname,\n"
					  "   p.prsname,\n"
					  "   np.nspname as pnspname\n"
					  "FROM pg_catalog.pg_ts_config c\n"
					  "   LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.cfgnamespace,\n"
					  " pg_catalog.pg_ts_parser p\n"
					  "   LEFT JOIN pg_catalog.pg_namespace np ON np.oid = p.prsnamespace\n"
					  "WHERE  p.oid = c.cfgparser\n"
		);

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "c.cfgname", NULL,
						  "pg_catalog.pg_ts_config_is_visible(c.oid)");

	appendPQExpBufferStr(&buf, "ORDER BY 3, 2;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	if (PQntuples(res) == 0)
	{
		if (!pset.quiet)
		{
			if (pattern)
				pg_log_error("Did not find any text search configuration named \"%s\".",
							 pattern);
			else
				pg_log_error("Did not find any text search configurations.");
		}
		PQclear(res);
		return false;
	}

	for (i = 0; i < PQntuples(res); i++)
	{
		const char *oid;
		const char *cfgname;
		const char *nspname = NULL;
		const char *prsname;
		const char *pnspname = NULL;

		oid = PQgetvalue(res, i, 0);
		cfgname = PQgetvalue(res, i, 1);
		if (!PQgetisnull(res, i, 2))
			nspname = PQgetvalue(res, i, 2);
		prsname = PQgetvalue(res, i, 3);
		if (!PQgetisnull(res, i, 4))
			pnspname = PQgetvalue(res, i, 4);

		if (!describeOneTSConfig(oid, nspname, cfgname, pnspname, prsname))
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