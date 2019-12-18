#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_18__ {scalar_t__ analyze; scalar_t__ summary; scalar_t__ costs; scalar_t__ buffers; scalar_t__ timing; } ;
struct TYPE_17__ {scalar_t__ skipData; } ;
struct TYPE_16__ {scalar_t__ commandType; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  int /*<<< orphan*/  QueryDesc ;
typedef  TYPE_1__ PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  TYPE_2__ IntoClause ;
typedef  TYPE_3__ ExplainState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_UTILITY ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/ * CreateIntoRelDestReceiver (TYPE_2__*) ; 
 int /*<<< orphan*/ * CreateQueryDesc (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int EXEC_FLAG_EXPLAIN_ONLY ; 
 int /*<<< orphan*/  ExecutorEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecutorFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecutorRun (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  ExecutorStart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExplainCloseGroup (char*,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ExplainOpenGroup (char*,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ExplainPrintJITSummary (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPrintPlan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPrintTriggers (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPropertyFloat (char*,char*,double,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeQueryDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int GetIntoRelEFlags (TYPE_2__*) ; 
 int INSTRUMENT_BUFFERS ; 
 int INSTRUMENT_ROWS ; 
 int INSTRUMENT_TIMER ; 
 double INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/  NoMovementScanDirection ; 
 int /*<<< orphan*/ * None_Receiver ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushCopiedSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateActiveSnapshotCommandId () ; 
 scalar_t__ elapsed_time (int /*<<< orphan*/ *) ; 

void
ExplainOnePlan(PlannedStmt *plannedstmt, IntoClause *into, ExplainState *es,
			   const char *queryString, ParamListInfo params,
			   QueryEnvironment *queryEnv, const instr_time *planduration)
{
	DestReceiver *dest;
	QueryDesc  *queryDesc;
	instr_time	starttime;
	double		totaltime = 0;
	int			eflags;
	int			instrument_option = 0;

	Assert(plannedstmt->commandType != CMD_UTILITY);

	if (es->analyze && es->timing)
		instrument_option |= INSTRUMENT_TIMER;
	else if (es->analyze)
		instrument_option |= INSTRUMENT_ROWS;

	if (es->buffers)
		instrument_option |= INSTRUMENT_BUFFERS;

	/*
	 * We always collect timing for the entire statement, even when node-level
	 * timing is off, so we don't look at es->timing here.  (We could skip
	 * this if !es->summary, but it's hardly worth the complication.)
	 */
	INSTR_TIME_SET_CURRENT(starttime);

	/*
	 * Use a snapshot with an updated command ID to ensure this query sees
	 * results of any previously executed queries.
	 */
	PushCopiedSnapshot(GetActiveSnapshot());
	UpdateActiveSnapshotCommandId();

	/*
	 * Normally we discard the query's output, but if explaining CREATE TABLE
	 * AS, we'd better use the appropriate tuple receiver.
	 */
	if (into)
		dest = CreateIntoRelDestReceiver(into);
	else
		dest = None_Receiver;

	/* Create a QueryDesc for the query */
	queryDesc = CreateQueryDesc(plannedstmt, queryString,
								GetActiveSnapshot(), InvalidSnapshot,
								dest, params, queryEnv, instrument_option);

	/* Select execution options */
	if (es->analyze)
		eflags = 0;				/* default run-to-completion flags */
	else
		eflags = EXEC_FLAG_EXPLAIN_ONLY;
	if (into)
		eflags |= GetIntoRelEFlags(into);

	/* call ExecutorStart to prepare the plan for execution */
	ExecutorStart(queryDesc, eflags);

	/* Execute the plan for statistics if asked for */
	if (es->analyze)
	{
		ScanDirection dir;

		/* EXPLAIN ANALYZE CREATE TABLE AS WITH NO DATA is weird */
		if (into && into->skipData)
			dir = NoMovementScanDirection;
		else
			dir = ForwardScanDirection;

		/* run the plan */
		ExecutorRun(queryDesc, dir, 0L, true);

		/* run cleanup too */
		ExecutorFinish(queryDesc);

		/* We can't run ExecutorEnd 'till we're done printing the stats... */
		totaltime += elapsed_time(&starttime);
	}

	ExplainOpenGroup("Query", NULL, true, es);

	/* Create textual dump of plan tree */
	ExplainPrintPlan(es, queryDesc);

	if (es->summary && planduration)
	{
		double		plantime = INSTR_TIME_GET_DOUBLE(*planduration);

		ExplainPropertyFloat("Planning Time", "ms", 1000.0 * plantime, 3, es);
	}

	/* Print info about runtime of triggers */
	if (es->analyze)
		ExplainPrintTriggers(es, queryDesc);

	/*
	 * Print info about JITing. Tied to es->costs because we don't want to
	 * display this in regression tests, as it'd cause output differences
	 * depending on build options.  Might want to separate that out from COSTS
	 * at a later stage.
	 */
	if (es->costs)
		ExplainPrintJITSummary(es, queryDesc);

	/*
	 * Close down the query and free resources.  Include time for this in the
	 * total execution time (although it should be pretty minimal).
	 */
	INSTR_TIME_SET_CURRENT(starttime);

	ExecutorEnd(queryDesc);

	FreeQueryDesc(queryDesc);

	PopActiveSnapshot();

	/* We need a CCI just in case query expanded to multiple plans */
	if (es->analyze)
		CommandCounterIncrement();

	totaltime += elapsed_time(&starttime);

	/*
	 * We only report execution time if we actually ran the query (that is,
	 * the user specified ANALYZE), and if summary reporting is enabled (the
	 * user can set SUMMARY OFF to not have the timing information included in
	 * the output).  By default, ANALYZE sets SUMMARY to true.
	 */
	if (es->summary && es->analyze)
		ExplainPropertyFloat("Execution Time", "ms", 1000.0 * totaltime, 3,
							 es);

	ExplainCloseGroup("Query", NULL, true, es);
}