#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* rDestroy ) (TYPE_2__*) ;} ;
struct TYPE_12__ {scalar_t__ stmts; char* sourceText; char* prepStmtName; int /*<<< orphan*/  atStart; int /*<<< orphan*/ * commandTag; int /*<<< orphan*/ * portalParams; } ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/ * ParamListInfo ;
typedef  TYPE_2__ DestReceiver ;
typedef  scalar_t__ CommandDest ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BeginCommand (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int COMPLETION_TAG_BUFSIZE ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 TYPE_2__* CreateDestReceiver (scalar_t__) ; 
 scalar_t__ DestRemote ; 
 scalar_t__ DestRemoteExecute ; 
 int /*<<< orphan*/  ERRCODE_IN_FAILED_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_CURSOR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EndCommand (char*,scalar_t__) ; 
 long FETCH_ALL ; 
 TYPE_1__* GetPortalByName (char const*) ; 
 scalar_t__ IsAbortedTransactionBlockState () ; 
 int /*<<< orphan*/  IsTransactionExitStmtList (scalar_t__) ; 
 int IsTransactionStmtList (scalar_t__) ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  NullCommand (scalar_t__) ; 
 int /*<<< orphan*/  PortalIsValid (TYPE_1__*) ; 
 int PortalRun (TYPE_1__*,long,int,int,TYPE_2__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  SetRemoteDestReceiverParams (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int check_log_duration (char*,int) ; 
 scalar_t__ check_log_statement (scalar_t__) ; 
 char const* debug_query_string ; 
 int /*<<< orphan*/  disable_statement_timeout () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_abort () ; 
 int /*<<< orphan*/  errdetail_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errhidestmt (int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  finish_xact_command () ; 
 int log_statement_stats ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pq_putemptymessage (char) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  set_ps_display (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  start_xact_command () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ whereToSendOutput ; 

__attribute__((used)) static void
exec_execute_message(const char *portal_name, long max_rows)
{
	CommandDest dest;
	DestReceiver *receiver;
	Portal		portal;
	bool		completed;
	char		completionTag[COMPLETION_TAG_BUFSIZE];
	const char *sourceText;
	const char *prepStmtName;
	ParamListInfo portalParams;
	bool		save_log_statement_stats = log_statement_stats;
	bool		is_xact_command;
	bool		execute_is_fetch;
	bool		was_logged = false;
	char		msec_str[32];

	/* Adjust destination to tell printtup.c what to do */
	dest = whereToSendOutput;
	if (dest == DestRemote)
		dest = DestRemoteExecute;

	portal = GetPortalByName(portal_name);
	if (!PortalIsValid(portal))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_CURSOR),
				 errmsg("portal \"%s\" does not exist", portal_name)));

	/*
	 * If the original query was a null string, just return
	 * EmptyQueryResponse.
	 */
	if (portal->commandTag == NULL)
	{
		Assert(portal->stmts == NIL);
		NullCommand(dest);
		return;
	}

	/* Does the portal contain a transaction command? */
	is_xact_command = IsTransactionStmtList(portal->stmts);

	/*
	 * We must copy the sourceText and prepStmtName into MessageContext in
	 * case the portal is destroyed during finish_xact_command. Can avoid the
	 * copy if it's not an xact command, though.
	 */
	if (is_xact_command)
	{
		sourceText = pstrdup(portal->sourceText);
		if (portal->prepStmtName)
			prepStmtName = pstrdup(portal->prepStmtName);
		else
			prepStmtName = "<unnamed>";

		/*
		 * An xact command shouldn't have any parameters, which is a good
		 * thing because they wouldn't be around after finish_xact_command.
		 */
		portalParams = NULL;
	}
	else
	{
		sourceText = portal->sourceText;
		if (portal->prepStmtName)
			prepStmtName = portal->prepStmtName;
		else
			prepStmtName = "<unnamed>";
		portalParams = portal->portalParams;
	}

	/*
	 * Report query to various monitoring facilities.
	 */
	debug_query_string = sourceText;

	pgstat_report_activity(STATE_RUNNING, sourceText);

	set_ps_display(portal->commandTag, false);

	if (save_log_statement_stats)
		ResetUsage();

	BeginCommand(portal->commandTag, dest);

	/*
	 * Create dest receiver in MessageContext (we don't want it in transaction
	 * context, because that may get deleted if portal contains VACUUM).
	 */
	receiver = CreateDestReceiver(dest);
	if (dest == DestRemoteExecute)
		SetRemoteDestReceiverParams(receiver, portal);

	/*
	 * Ensure we are in a transaction command (this should normally be the
	 * case already due to prior BIND).
	 */
	start_xact_command();

	/*
	 * If we re-issue an Execute protocol request against an existing portal,
	 * then we are only fetching more rows rather than completely re-executing
	 * the query from the start. atStart is never reset for a v3 portal, so we
	 * are safe to use this check.
	 */
	execute_is_fetch = !portal->atStart;

	/* Log immediately if dictated by log_statement */
	if (check_log_statement(portal->stmts))
	{
		ereport(LOG,
				(errmsg("%s %s%s%s: %s",
						execute_is_fetch ?
						_("execute fetch from") :
						_("execute"),
						prepStmtName,
						*portal_name ? "/" : "",
						*portal_name ? portal_name : "",
						sourceText),
				 errhidestmt(true),
				 errdetail_params(portalParams)));
		was_logged = true;
	}

	/*
	 * If we are in aborted transaction state, the only portals we can
	 * actually run are those containing COMMIT or ROLLBACK commands.
	 */
	if (IsAbortedTransactionBlockState() &&
		!IsTransactionExitStmtList(portal->stmts))
		ereport(ERROR,
				(errcode(ERRCODE_IN_FAILED_SQL_TRANSACTION),
				 errmsg("current transaction is aborted, "
						"commands ignored until end of transaction block"),
				 errdetail_abort()));

	/* Check for cancel signal before we start execution */
	CHECK_FOR_INTERRUPTS();

	/*
	 * Okay to run the portal.
	 */
	if (max_rows <= 0)
		max_rows = FETCH_ALL;

	completed = PortalRun(portal,
						  max_rows,
						  true, /* always top level */
						  !execute_is_fetch && max_rows == FETCH_ALL,
						  receiver,
						  receiver,
						  completionTag);

	receiver->rDestroy(receiver);

	if (completed)
	{
		if (is_xact_command)
		{
			/*
			 * If this was a transaction control statement, commit it.  We
			 * will start a new xact command for the next command (if any).
			 */
			finish_xact_command();
		}
		else
		{
			/*
			 * We need a CommandCounterIncrement after every query, except
			 * those that start or end a transaction block.
			 */
			CommandCounterIncrement();

			/*
			 * Disable statement timeout whenever we complete an Execute
			 * message.  The next protocol message will start a fresh timeout.
			 */
			disable_statement_timeout();
		}

		/* Send appropriate CommandComplete to client */
		EndCommand(completionTag, dest);
	}
	else
	{
		/* Portal run not complete, so send PortalSuspended */
		if (whereToSendOutput == DestRemote)
			pq_putemptymessage('s');
	}

	/*
	 * Emit duration logging if appropriate.
	 */
	switch (check_log_duration(msec_str, was_logged))
	{
		case 1:
			ereport(LOG,
					(errmsg("duration: %s ms", msec_str),
					 errhidestmt(true)));
			break;
		case 2:
			ereport(LOG,
					(errmsg("duration: %s ms  %s %s%s%s: %s",
							msec_str,
							execute_is_fetch ?
							_("execute fetch from") :
							_("execute"),
							prepStmtName,
							*portal_name ? "/" : "",
							*portal_name ? portal_name : "",
							sourceText),
					 errhidestmt(true),
					 errdetail_params(portalParams)));
			break;
	}

	if (save_log_statement_stats)
		ShowUsage("EXECUTE MESSAGE STATISTICS");

	debug_query_string = NULL;
}