#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
typedef  int /*<<< orphan*/  instr_time ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ encoding; } ;
struct TYPE_5__ {TYPE_1__ topt; } ;
struct TYPE_6__ {scalar_t__ echo; scalar_t__ on_error_rollback; int sversion; int gdesc_flag; scalar_t__ fetch_count; int gexec_flag; int crosstab_flag; scalar_t__ encoding; int g_expanded; int /*<<< orphan*/ ** ctv_args; int /*<<< orphan*/ * gset_prefix; int /*<<< orphan*/ * gfname; int /*<<< orphan*/  vars; TYPE_2__ popt; int /*<<< orphan*/  db; scalar_t__ timing; scalar_t__ cur_cmd_interactive; int /*<<< orphan*/  autocommit; scalar_t__ logfile; scalar_t__ singlestep; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int PGTransactionStatusType ;

/* Variables and functions */
 int /*<<< orphan*/  ClearOrSaveResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConnectionUp () ; 
 int DescribeQuery (char const*,double*) ; 
 int ExecQueryUsingCursor (char const*,double*) ; 
 double INSTR_TIME_GET_MILLISEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
#define  PQTRANS_ACTIVE 132 
#define  PQTRANS_IDLE 131 
#define  PQTRANS_INERROR 130 
#define  PQTRANS_INTRANS 129 
#define  PQTRANS_UNKNOWN 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 scalar_t__ PQclientEncoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQcmdStatus (int /*<<< orphan*/ *) ; 
 char const* PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQtransactionStatus (int /*<<< orphan*/ ) ; 
 scalar_t__ PSQL_ECHO_ERRORS ; 
 scalar_t__ PSQL_ECHO_QUERIES ; 
 scalar_t__ PSQL_ERROR_ROLLBACK_OFF ; 
 scalar_t__ PSQL_ERROR_ROLLBACK_ON ; 
 int /*<<< orphan*/  PrintNotifications () ; 
 int PrintQueryResults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintTiming (double) ; 
 int ProcessResult (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 int /*<<< orphan*/  SetVariable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 scalar_t__ cancel_pressed ; 
 int /*<<< orphan*/  command_no_begin (char const*) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_select_command (char const*) ; 
 int lengthof (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pg_encoding_to_char (scalar_t__) ; 
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  puts (char const*) ; 
 scalar_t__ stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

bool
SendQuery(const char *query)
{
	PGresult   *results;
	PGTransactionStatusType transaction_status;
	double		elapsed_msec = 0;
	bool		OK = false;
	int			i;
	bool		on_error_rollback_savepoint = false;
	static bool on_error_rollback_warning = false;

	if (!pset.db)
	{
		pg_log_error("You are currently not connected to a database.");
		goto sendquery_cleanup;
	}

	if (pset.singlestep)
	{
		char		buf[3];

		fflush(stderr);
		printf(_("***(Single step mode: verify command)*******************************************\n"
				 "%s\n"
				 "***(press return to proceed or enter x and return to cancel)********************\n"),
			   query);
		fflush(stdout);
		if (fgets(buf, sizeof(buf), stdin) != NULL)
			if (buf[0] == 'x')
				goto sendquery_cleanup;
		if (cancel_pressed)
			goto sendquery_cleanup;
	}
	else if (pset.echo == PSQL_ECHO_QUERIES)
	{
		puts(query);
		fflush(stdout);
	}

	if (pset.logfile)
	{
		fprintf(pset.logfile,
				_("********* QUERY **********\n"
				  "%s\n"
				  "**************************\n\n"), query);
		fflush(pset.logfile);
	}

	SetCancelConn();

	transaction_status = PQtransactionStatus(pset.db);

	if (transaction_status == PQTRANS_IDLE &&
		!pset.autocommit &&
		!command_no_begin(query))
	{
		results = PQexec(pset.db, "BEGIN");
		if (PQresultStatus(results) != PGRES_COMMAND_OK)
		{
			pg_log_info("%s", PQerrorMessage(pset.db));
			ClearOrSaveResult(results);
			ResetCancelConn();
			goto sendquery_cleanup;
		}
		ClearOrSaveResult(results);
		transaction_status = PQtransactionStatus(pset.db);
	}

	if (transaction_status == PQTRANS_INTRANS &&
		pset.on_error_rollback != PSQL_ERROR_ROLLBACK_OFF &&
		(pset.cur_cmd_interactive ||
		 pset.on_error_rollback == PSQL_ERROR_ROLLBACK_ON))
	{
		if (on_error_rollback_warning == false && pset.sversion < 80000)
		{
			char		sverbuf[32];

			pg_log_warning("The server (version %s) does not support savepoints for ON_ERROR_ROLLBACK.",
						   formatPGVersionNumber(pset.sversion, false,
												 sverbuf, sizeof(sverbuf)));
			on_error_rollback_warning = true;
		}
		else
		{
			results = PQexec(pset.db, "SAVEPOINT pg_psql_temporary_savepoint");
			if (PQresultStatus(results) != PGRES_COMMAND_OK)
			{
				pg_log_info("%s", PQerrorMessage(pset.db));
				ClearOrSaveResult(results);
				ResetCancelConn();
				goto sendquery_cleanup;
			}
			ClearOrSaveResult(results);
			on_error_rollback_savepoint = true;
		}
	}

	if (pset.gdesc_flag)
	{
		/* Describe query's result columns, without executing it */
		OK = DescribeQuery(query, &elapsed_msec);
		ResetCancelConn();
		results = NULL;			/* PQclear(NULL) does nothing */
	}
	else if (pset.fetch_count <= 0 || pset.gexec_flag ||
			 pset.crosstab_flag || !is_select_command(query))
	{
		/* Default fetch-it-all-and-print mode */
		instr_time	before,
					after;

		if (pset.timing)
			INSTR_TIME_SET_CURRENT(before);

		results = PQexec(pset.db, query);

		/* these operations are included in the timing result: */
		ResetCancelConn();
		OK = ProcessResult(&results);

		if (pset.timing)
		{
			INSTR_TIME_SET_CURRENT(after);
			INSTR_TIME_SUBTRACT(after, before);
			elapsed_msec = INSTR_TIME_GET_MILLISEC(after);
		}

		/* but printing results isn't: */
		if (OK && results)
			OK = PrintQueryResults(results);
	}
	else
	{
		/* Fetch-in-segments mode */
		OK = ExecQueryUsingCursor(query, &elapsed_msec);
		ResetCancelConn();
		results = NULL;			/* PQclear(NULL) does nothing */
	}

	if (!OK && pset.echo == PSQL_ECHO_ERRORS)
		pg_log_info("STATEMENT:  %s", query);

	/* If we made a temporary savepoint, possibly release/rollback */
	if (on_error_rollback_savepoint)
	{
		const char *svptcmd = NULL;

		transaction_status = PQtransactionStatus(pset.db);

		switch (transaction_status)
		{
			case PQTRANS_INERROR:
				/* We always rollback on an error */
				svptcmd = "ROLLBACK TO pg_psql_temporary_savepoint";
				break;

			case PQTRANS_IDLE:
				/* If they are no longer in a transaction, then do nothing */
				break;

			case PQTRANS_INTRANS:

				/*
				 * Do nothing if they are messing with savepoints themselves:
				 * If the user did RELEASE or ROLLBACK, our savepoint is gone.
				 * If they issued a SAVEPOINT, releasing ours would remove
				 * theirs.
				 */
				if (results &&
					(strcmp(PQcmdStatus(results), "SAVEPOINT") == 0 ||
					 strcmp(PQcmdStatus(results), "RELEASE") == 0 ||
					 strcmp(PQcmdStatus(results), "ROLLBACK") == 0))
					svptcmd = NULL;
				else
					svptcmd = "RELEASE pg_psql_temporary_savepoint";
				break;

			case PQTRANS_ACTIVE:
			case PQTRANS_UNKNOWN:
			default:
				OK = false;
				/* PQTRANS_UNKNOWN is expected given a broken connection. */
				if (transaction_status != PQTRANS_UNKNOWN || ConnectionUp())
					pg_log_error("unexpected transaction status (%d)",
								 transaction_status);
				break;
		}

		if (svptcmd)
		{
			PGresult   *svptres;

			svptres = PQexec(pset.db, svptcmd);
			if (PQresultStatus(svptres) != PGRES_COMMAND_OK)
			{
				pg_log_info("%s", PQerrorMessage(pset.db));
				ClearOrSaveResult(svptres);
				OK = false;

				PQclear(results);
				ResetCancelConn();
				goto sendquery_cleanup;
			}
			PQclear(svptres);
		}
	}

	ClearOrSaveResult(results);

	/* Possible microtiming output */
	if (pset.timing)
		PrintTiming(elapsed_msec);

	/* check for events that may occur during query execution */

	if (pset.encoding != PQclientEncoding(pset.db) &&
		PQclientEncoding(pset.db) >= 0)
	{
		/* track effects of SET CLIENT_ENCODING */
		pset.encoding = PQclientEncoding(pset.db);
		pset.popt.topt.encoding = pset.encoding;
		SetVariable(pset.vars, "ENCODING",
					pg_encoding_to_char(pset.encoding));
	}

	PrintNotifications();

	/* perform cleanup that should occur after any attempted query */

sendquery_cleanup:

	/* reset \g's output-to-filename trigger */
	if (pset.gfname)
	{
		free(pset.gfname);
		pset.gfname = NULL;
	}

	/* reset \gx's expanded-mode flag */
	pset.g_expanded = false;

	/* reset \gset trigger */
	if (pset.gset_prefix)
	{
		free(pset.gset_prefix);
		pset.gset_prefix = NULL;
	}

	/* reset \gdesc trigger */
	pset.gdesc_flag = false;

	/* reset \gexec trigger */
	pset.gexec_flag = false;

	/* reset \crosstabview trigger */
	pset.crosstab_flag = false;
	for (i = 0; i < lengthof(pset.ctv_args); i++)
	{
		pg_free(pset.ctv_args[i]);
		pset.ctv_args[i] = NULL;
	}

	return OK;
}