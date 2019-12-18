#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ echo_hidden; int /*<<< orphan*/  db; scalar_t__ logfile; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearOrSaveResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ PSQL_ECHO_HIDDEN_NOEXEC ; 
 scalar_t__ PSQL_ECHO_HIDDEN_OFF ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_1__ pset ; 
 scalar_t__ stdout ; 

PGresult *
PSQLexec(const char *query)
{
	PGresult   *res;

	if (!pset.db)
	{
		pg_log_error("You are currently not connected to a database.");
		return NULL;
	}

	if (pset.echo_hidden != PSQL_ECHO_HIDDEN_OFF)
	{
		printf(_("********* QUERY **********\n"
				 "%s\n"
				 "**************************\n\n"), query);
		fflush(stdout);
		if (pset.logfile)
		{
			fprintf(pset.logfile,
					_("********* QUERY **********\n"
					  "%s\n"
					  "**************************\n\n"), query);
			fflush(pset.logfile);
		}

		if (pset.echo_hidden == PSQL_ECHO_HIDDEN_NOEXEC)
			return NULL;
	}

	SetCancelConn();

	res = PQexec(pset.db, query);

	ResetCancelConn();

	if (!AcceptResult(res))
	{
		ClearOrSaveResult(res);
		res = NULL;
	}

	return res;
}