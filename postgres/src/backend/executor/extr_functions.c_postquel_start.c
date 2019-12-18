#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  status; TYPE_7__* qd; scalar_t__ lazyEval; int /*<<< orphan*/  stmt; scalar_t__ setsResult; } ;
typedef  TYPE_2__ execution_state ;
struct TYPE_13__ {scalar_t__ operation; int /*<<< orphan*/ * queryEnv; } ;
struct TYPE_9__ {scalar_t__ mydest; } ;
struct TYPE_12__ {int /*<<< orphan*/  filter; int /*<<< orphan*/  cxt; int /*<<< orphan*/  tstore; TYPE_1__ pub; } ;
struct TYPE_11__ {int /*<<< orphan*/  paramLI; int /*<<< orphan*/  src; int /*<<< orphan*/  junkFilter; int /*<<< orphan*/  tstore; } ;
typedef  TYPE_3__* SQLFunctionCachePtr ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_4__ DR_sqlfunction ;

/* Variables and functions */
 int ActiveSnapshotSet () ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_UTILITY ; 
 int /*<<< orphan*/ * CreateDestReceiver (scalar_t__) ; 
 TYPE_7__* CreateQueryDesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ DestSQLFunction ; 
 int EXEC_FLAG_SKIP_TRIGGERS ; 
 int /*<<< orphan*/  ExecutorStart (TYPE_7__*,int) ; 
 int /*<<< orphan*/  F_EXEC_RUN ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/ * None_Receiver ; 

__attribute__((used)) static void
postquel_start(execution_state *es, SQLFunctionCachePtr fcache)
{
	DestReceiver *dest;

	Assert(es->qd == NULL);

	/* Caller should have ensured a suitable snapshot is active */
	Assert(ActiveSnapshotSet());

	/*
	 * If this query produces the function result, send its output to the
	 * tuplestore; else discard any output.
	 */
	if (es->setsResult)
	{
		DR_sqlfunction *myState;

		dest = CreateDestReceiver(DestSQLFunction);
		/* pass down the needed info to the dest receiver routines */
		myState = (DR_sqlfunction *) dest;
		Assert(myState->pub.mydest == DestSQLFunction);
		myState->tstore = fcache->tstore;
		myState->cxt = CurrentMemoryContext;
		myState->filter = fcache->junkFilter;
	}
	else
		dest = None_Receiver;

	es->qd = CreateQueryDesc(es->stmt,
							 fcache->src,
							 GetActiveSnapshot(),
							 InvalidSnapshot,
							 dest,
							 fcache->paramLI,
							 es->qd ? es->qd->queryEnv : NULL,
							 0);

	/* Utility commands don't need Executor. */
	if (es->qd->operation != CMD_UTILITY)
	{
		/*
		 * In lazyEval mode, do not let the executor set up an AfterTrigger
		 * context.  This is necessary not just an optimization, because we
		 * mustn't exit from the function execution with a stacked
		 * AfterTrigger level still active.  We are careful not to select
		 * lazyEval mode for any statement that could possibly queue triggers.
		 */
		int			eflags;

		if (es->lazyEval)
			eflags = EXEC_FLAG_SKIP_TRIGGERS;
		else
			eflags = 0;			/* default run-to-completion flags */
		ExecutorStart(es->qd, eflags);
	}

	es->status = F_EXEC_RUN;
}