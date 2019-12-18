#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* title; } ;
typedef  TYPE_1__ printQueryOpt ;
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_6__ {scalar_t__ timing; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  logfile; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearOrSaveResult (int /*<<< orphan*/ *) ; 
 double INSTR_TIME_GET_MILLISEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PGRES_COMMAND_OK 133 
#define  PGRES_COPY_BOTH 132 
#define  PGRES_COPY_IN 131 
#define  PGRES_COPY_OUT 130 
#define  PGRES_EMPTY_QUERY 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQcmdStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintTiming (double) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ pset ; 

int
PSQLexecWatch(const char *query, const printQueryOpt *opt)
{
	PGresult   *res;
	double		elapsed_msec = 0;
	instr_time	before;
	instr_time	after;

	if (!pset.db)
	{
		pg_log_error("You are currently not connected to a database.");
		return 0;
	}

	SetCancelConn();

	if (pset.timing)
		INSTR_TIME_SET_CURRENT(before);

	res = PQexec(pset.db, query);

	ResetCancelConn();

	if (!AcceptResult(res))
	{
		ClearOrSaveResult(res);
		return 0;
	}

	if (pset.timing)
	{
		INSTR_TIME_SET_CURRENT(after);
		INSTR_TIME_SUBTRACT(after, before);
		elapsed_msec = INSTR_TIME_GET_MILLISEC(after);
	}

	/*
	 * If SIGINT is sent while the query is processing, the interrupt will be
	 * consumed.  The user's intention, though, is to cancel the entire watch
	 * process, so detect a sent cancellation request and exit in this case.
	 */
	if (cancel_pressed)
	{
		PQclear(res);
		return 0;
	}

	switch (PQresultStatus(res))
	{
		case PGRES_TUPLES_OK:
			printQuery(res, opt, pset.queryFout, false, pset.logfile);
			break;

		case PGRES_COMMAND_OK:
			fprintf(pset.queryFout, "%s\n%s\n\n", opt->title, PQcmdStatus(res));
			break;

		case PGRES_EMPTY_QUERY:
			pg_log_error("\\watch cannot be used with an empty query");
			PQclear(res);
			return -1;

		case PGRES_COPY_OUT:
		case PGRES_COPY_IN:
		case PGRES_COPY_BOTH:
			pg_log_error("\\watch cannot be used with COPY");
			PQclear(res);
			return -1;

		default:
			pg_log_error("unexpected result status for \\watch");
			PQclear(res);
			return -1;
	}

	PQclear(res);

	fflush(pset.queryFout);

	/* Possible microtiming output */
	if (pset.timing)
		PrintTiming(elapsed_msec);

	return 1;
}