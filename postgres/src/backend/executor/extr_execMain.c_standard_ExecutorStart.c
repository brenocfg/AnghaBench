#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ paramExecTypes; scalar_t__ rowMarks; int /*<<< orphan*/  jitFlags; int /*<<< orphan*/  hasModifyingCTE; } ;
struct TYPE_8__ {int es_top_eflags; int /*<<< orphan*/  es_jit_flags; int /*<<< orphan*/  es_instrument; void* es_crosscheck_snapshot; void* es_snapshot; void* es_output_cid; int /*<<< orphan*/  es_queryEnv; int /*<<< orphan*/  es_sourceText; int /*<<< orphan*/ * es_param_exec_vals; int /*<<< orphan*/  es_param_list_info; int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_7__ {int operation; TYPE_5__* plannedstmt; int /*<<< orphan*/  instrument_options; int /*<<< orphan*/  crosscheck_snapshot; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  queryEnv; int /*<<< orphan*/  sourceText; int /*<<< orphan*/  params; TYPE_2__* estate; } ;
typedef  TYPE_1__ QueryDesc ;
typedef  int /*<<< orphan*/  ParamExecData ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerBeginQuery () ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  CMD_DELETE 131 
#define  CMD_INSERT 130 
#define  CMD_SELECT 129 
#define  CMD_UPDATE 128 
 TYPE_2__* CreateExecutorState () ; 
 int /*<<< orphan*/  ERROR ; 
 int EXEC_FLAG_EXPLAIN_ONLY ; 
 int EXEC_FLAG_SKIP_TRIGGERS ; 
 int /*<<< orphan*/  ExecCheckXactReadOnly (TYPE_5__*) ; 
 void* GetCurrentCommandId (int) ; 
 int /*<<< orphan*/  InitPlan (TYPE_1__*,int) ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 void* RegisterSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ XactReadOnly ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int list_length (scalar_t__) ; 
 scalar_t__ palloc0 (int) ; 

void
standard_ExecutorStart(QueryDesc *queryDesc, int eflags)
{
	EState	   *estate;
	MemoryContext oldcontext;

	/* sanity checks: queryDesc must not be started already */
	Assert(queryDesc != NULL);
	Assert(queryDesc->estate == NULL);

	/*
	 * If the transaction is read-only, we need to check if any writes are
	 * planned to non-temporary tables.  EXPLAIN is considered read-only.
	 *
	 * Don't allow writes in parallel mode.  Supporting UPDATE and DELETE
	 * would require (a) storing the combocid hash in shared memory, rather
	 * than synchronizing it just once at the start of parallelism, and (b) an
	 * alternative to heap_update()'s reliance on xmax for mutual exclusion.
	 * INSERT may have no such troubles, but we forbid it to simplify the
	 * checks.
	 *
	 * We have lower-level defenses in CommandCounterIncrement and elsewhere
	 * against performing unsafe operations in parallel mode, but this gives a
	 * more user-friendly error message.
	 */
	if ((XactReadOnly || IsInParallelMode()) &&
		!(eflags & EXEC_FLAG_EXPLAIN_ONLY))
		ExecCheckXactReadOnly(queryDesc->plannedstmt);

	/*
	 * Build EState, switch into per-query memory context for startup.
	 */
	estate = CreateExecutorState();
	queryDesc->estate = estate;

	oldcontext = MemoryContextSwitchTo(estate->es_query_cxt);

	/*
	 * Fill in external parameters, if any, from queryDesc; and allocate
	 * workspace for internal parameters
	 */
	estate->es_param_list_info = queryDesc->params;

	if (queryDesc->plannedstmt->paramExecTypes != NIL)
	{
		int			nParamExec;

		nParamExec = list_length(queryDesc->plannedstmt->paramExecTypes);
		estate->es_param_exec_vals = (ParamExecData *)
			palloc0(nParamExec * sizeof(ParamExecData));
	}

	estate->es_sourceText = queryDesc->sourceText;

	/*
	 * Fill in the query environment, if any, from queryDesc.
	 */
	estate->es_queryEnv = queryDesc->queryEnv;

	/*
	 * If non-read-only query, set the command ID to mark output tuples with
	 */
	switch (queryDesc->operation)
	{
		case CMD_SELECT:

			/*
			 * SELECT FOR [KEY] UPDATE/SHARE and modifying CTEs need to mark
			 * tuples
			 */
			if (queryDesc->plannedstmt->rowMarks != NIL ||
				queryDesc->plannedstmt->hasModifyingCTE)
				estate->es_output_cid = GetCurrentCommandId(true);

			/*
			 * A SELECT without modifying CTEs can't possibly queue triggers,
			 * so force skip-triggers mode. This is just a marginal efficiency
			 * hack, since AfterTriggerBeginQuery/AfterTriggerEndQuery aren't
			 * all that expensive, but we might as well do it.
			 */
			if (!queryDesc->plannedstmt->hasModifyingCTE)
				eflags |= EXEC_FLAG_SKIP_TRIGGERS;
			break;

		case CMD_INSERT:
		case CMD_DELETE:
		case CMD_UPDATE:
			estate->es_output_cid = GetCurrentCommandId(true);
			break;

		default:
			elog(ERROR, "unrecognized operation code: %d",
				 (int) queryDesc->operation);
			break;
	}

	/*
	 * Copy other important information into the EState
	 */
	estate->es_snapshot = RegisterSnapshot(queryDesc->snapshot);
	estate->es_crosscheck_snapshot = RegisterSnapshot(queryDesc->crosscheck_snapshot);
	estate->es_top_eflags = eflags;
	estate->es_instrument = queryDesc->instrument_options;
	estate->es_jit_flags = queryDesc->plannedstmt->jitFlags;

	/*
	 * Set up an AFTER-trigger statement context, unless told not to, or
	 * unless it's EXPLAIN-only mode (when ExecutorFinish won't be called).
	 */
	if (!(eflags & (EXEC_FLAG_SKIP_TRIGGERS | EXEC_FLAG_EXPLAIN_ONLY)))
		AfterTriggerBeginQuery();

	/*
	 * Initialize the plan state tree
	 */
	InitPlan(queryDesc, eflags);

	MemoryContextSwitchTo(oldcontext);
}