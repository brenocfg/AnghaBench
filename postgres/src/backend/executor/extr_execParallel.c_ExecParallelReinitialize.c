#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  toc; } ;
struct TYPE_17__ {int /*<<< orphan*/ * es_query_dsa; } ;
struct TYPE_16__ {int /*<<< orphan*/  param_exec; } ;
struct TYPE_15__ {int finished; TYPE_7__* pcxt; int /*<<< orphan*/ * area; int /*<<< orphan*/  param_exec; int /*<<< orphan*/ * reader; int /*<<< orphan*/  tqueue; } ;
struct TYPE_14__ {TYPE_4__* state; } ;
typedef  TYPE_1__ PlanState ;
typedef  TYPE_2__ ParallelExecutorInfo ;
typedef  TYPE_3__ FixedParallelExecutorState ;
typedef  TYPE_4__ EState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecParallelReInitializeDSM (TYPE_1__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ExecParallelSetupTupleQueues (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ExecSetParamPlanMulti (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPerTupleExprContext (TYPE_4__*) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  PARALLEL_KEY_EXECUTOR_FIXED ; 
 int /*<<< orphan*/  ReinitializeParallelDSM (TYPE_7__*) ; 
 int /*<<< orphan*/  SerializeParamExecParams (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ExecParallelReinitialize(PlanState *planstate,
						 ParallelExecutorInfo *pei,
						 Bitmapset *sendParams)
{
	EState	   *estate = planstate->state;
	FixedParallelExecutorState *fpes;

	/* Old workers must already be shut down */
	Assert(pei->finished);

	/*
	 * Force any initplan outputs that we're going to pass to workers to be
	 * evaluated, if they weren't already (see comments in
	 * ExecInitParallelPlan).
	 */
	ExecSetParamPlanMulti(sendParams, GetPerTupleExprContext(estate));

	ReinitializeParallelDSM(pei->pcxt);
	pei->tqueue = ExecParallelSetupTupleQueues(pei->pcxt, true);
	pei->reader = NULL;
	pei->finished = false;

	fpes = shm_toc_lookup(pei->pcxt->toc, PARALLEL_KEY_EXECUTOR_FIXED, false);

	/* Free any serialized parameters from the last round. */
	if (DsaPointerIsValid(fpes->param_exec))
	{
		dsa_free(pei->area, fpes->param_exec);
		fpes->param_exec = InvalidDsaPointer;
	}

	/* Serialize current parameter values if required. */
	if (!bms_is_empty(sendParams))
	{
		pei->param_exec = SerializeParamExecParams(estate, sendParams,
												   pei->area);
		fpes->param_exec = pei->param_exec;
	}

	/* Traverse plan tree and let each child node reset associated state. */
	estate->es_query_dsa = pei->area;
	ExecParallelReInitializeDSM(planstate, pei->pcxt);
	estate->es_query_dsa = NULL;
}