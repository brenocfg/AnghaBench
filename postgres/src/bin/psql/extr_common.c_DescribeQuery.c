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
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_9__ {int /*<<< orphan*/  queryFout; scalar_t__ timing; int /*<<< orphan*/  db; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int AcceptResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearOrSaveResult (int /*<<< orphan*/ *) ; 
 scalar_t__ INSTR_TIME_GET_MILLISEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQdescribePrepared (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQescapeLiteral (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfmod (int /*<<< orphan*/ *,int) ; 
 char* PQfname (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 int /*<<< orphan*/  PQftype (int /*<<< orphan*/ *,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQprepare (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PrintQueryResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetResultVariables (int /*<<< orphan*/ *,int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static bool
DescribeQuery(const char *query, double *elapsed_msec)
{
	PGresult   *results;
	bool		OK;
	instr_time	before,
				after;

	*elapsed_msec = 0;

	if (pset.timing)
		INSTR_TIME_SET_CURRENT(before);

	/*
	 * To parse the query but not execute it, we prepare it, using the unnamed
	 * prepared statement.  This is invisible to psql users, since there's no
	 * way to access the unnamed prepared statement from psql user space. The
	 * next Parse or Query protocol message would overwrite the statement
	 * anyway.  (So there's no great need to clear it when done, which is a
	 * good thing because libpq provides no easy way to do that.)
	 */
	results = PQprepare(pset.db, "", query, 0, NULL);
	if (PQresultStatus(results) != PGRES_COMMAND_OK)
	{
		pg_log_info("%s", PQerrorMessage(pset.db));
		SetResultVariables(results, false);
		ClearOrSaveResult(results);
		return false;
	}
	PQclear(results);

	results = PQdescribePrepared(pset.db, "");
	OK = AcceptResult(results) &&
		(PQresultStatus(results) == PGRES_COMMAND_OK);
	if (OK && results)
	{
		if (PQnfields(results) > 0)
		{
			PQExpBufferData buf;
			int			i;

			initPQExpBuffer(&buf);

			printfPQExpBuffer(&buf,
							  "SELECT name AS \"%s\", pg_catalog.format_type(tp, tpm) AS \"%s\"\n"
							  "FROM (VALUES ",
							  gettext_noop("Column"),
							  gettext_noop("Type"));

			for (i = 0; i < PQnfields(results); i++)
			{
				const char *name;
				char	   *escname;

				if (i > 0)
					appendPQExpBufferStr(&buf, ",");

				name = PQfname(results, i);
				escname = PQescapeLiteral(pset.db, name, strlen(name));

				if (escname == NULL)
				{
					pg_log_info("%s", PQerrorMessage(pset.db));
					PQclear(results);
					termPQExpBuffer(&buf);
					return false;
				}

				appendPQExpBuffer(&buf, "(%s, '%u'::pg_catalog.oid, %d)",
								  escname,
								  PQftype(results, i),
								  PQfmod(results, i));

				PQfreemem(escname);
			}

			appendPQExpBufferStr(&buf, ") s(name, tp, tpm)");
			PQclear(results);

			results = PQexec(pset.db, buf.data);
			OK = AcceptResult(results);

			if (pset.timing)
			{
				INSTR_TIME_SET_CURRENT(after);
				INSTR_TIME_SUBTRACT(after, before);
				*elapsed_msec += INSTR_TIME_GET_MILLISEC(after);
			}

			if (OK && results)
				OK = PrintQueryResults(results);

			termPQExpBuffer(&buf);
		}
		else
			fprintf(pset.queryFout,
					_("The command has no result, or the result has no columns.\n"));
	}

	SetResultVariables(results, OK);
	ClearOrSaveResult(results);

	return OK;
}