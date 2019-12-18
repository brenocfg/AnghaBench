#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_toc ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_35__ {int /*<<< orphan*/  (* rDestroy ) (TYPE_9__*) ;} ;
struct TYPE_34__ {scalar_t__ tuples_needed; int /*<<< orphan*/  param_exec; int /*<<< orphan*/  eflags; int /*<<< orphan*/  jit_flags; } ;
struct TYPE_33__ {int /*<<< orphan*/ * seg; int /*<<< orphan*/ * toc; } ;
struct TYPE_32__ {TYPE_11__* estate; TYPE_17__* planstate; TYPE_1__* plannedstmt; int /*<<< orphan*/  sourceText; } ;
struct TYPE_31__ {int instrument_options; } ;
struct TYPE_30__ {size_t num_workers; int /*<<< orphan*/ * jit_instr; } ;
struct TYPE_29__ {int /*<<< orphan*/  instr; } ;
struct TYPE_28__ {int /*<<< orphan*/ * es_query_dsa; } ;
struct TYPE_27__ {int /*<<< orphan*/  jitFlags; } ;
struct TYPE_26__ {TYPE_2__* state; } ;
struct TYPE_25__ {TYPE_3__* es_jit; } ;
typedef  TYPE_4__ SharedJitInstrumentation ;
typedef  TYPE_5__ SharedExecutorInstrumentation ;
typedef  TYPE_6__ QueryDesc ;
typedef  TYPE_7__ ParallelWorkerContext ;
typedef  TYPE_8__ FixedParallelExecutorState ;
typedef  TYPE_9__ DestReceiver ;
typedef  int /*<<< orphan*/  BufferUsage ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 TYPE_6__* ExecParallelGetQueryDesc (int /*<<< orphan*/ *,TYPE_9__*,int) ; 
 TYPE_9__* ExecParallelGetReceiver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecParallelInitializeWorker (TYPE_17__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ExecParallelReportInstrumentation (TYPE_17__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecSetTupleBound (scalar_t__,TYPE_17__*) ; 
 int /*<<< orphan*/  ExecutorEnd (TYPE_6__*) ; 
 int /*<<< orphan*/  ExecutorFinish (TYPE_6__*) ; 
 int /*<<< orphan*/  ExecutorRun (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ExecutorStart (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeQueryDesc (TYPE_6__*) ; 
 int /*<<< orphan*/  InstrEndParallelQuery (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstrStartParallelQuery () ; 
 int /*<<< orphan*/  PARALLEL_KEY_BUFFER_USAGE ; 
 int /*<<< orphan*/  PARALLEL_KEY_DSA ; 
 int /*<<< orphan*/  PARALLEL_KEY_EXECUTOR_FIXED ; 
 int /*<<< orphan*/  PARALLEL_KEY_INSTRUMENTATION ; 
 int /*<<< orphan*/  PARALLEL_KEY_JIT_INSTRUMENTATION ; 
 size_t ParallelWorkerNumber ; 
 int /*<<< orphan*/  RestoreParamExecParams (char*,TYPE_11__*) ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  debug_query_string ; 
 int /*<<< orphan*/ * dsa_attach_in_place (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_detach (int /*<<< orphan*/ *) ; 
 char* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* shm_toc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*) ; 

void
ParallelQueryMain(dsm_segment *seg, shm_toc *toc)
{
	FixedParallelExecutorState *fpes;
	BufferUsage *buffer_usage;
	DestReceiver *receiver;
	QueryDesc  *queryDesc;
	SharedExecutorInstrumentation *instrumentation;
	SharedJitInstrumentation *jit_instrumentation;
	int			instrument_options = 0;
	void	   *area_space;
	dsa_area   *area;
	ParallelWorkerContext pwcxt;

	/* Get fixed-size state. */
	fpes = shm_toc_lookup(toc, PARALLEL_KEY_EXECUTOR_FIXED, false);

	/* Set up DestReceiver, SharedExecutorInstrumentation, and QueryDesc. */
	receiver = ExecParallelGetReceiver(seg, toc);
	instrumentation = shm_toc_lookup(toc, PARALLEL_KEY_INSTRUMENTATION, true);
	if (instrumentation != NULL)
		instrument_options = instrumentation->instrument_options;
	jit_instrumentation = shm_toc_lookup(toc, PARALLEL_KEY_JIT_INSTRUMENTATION,
										 true);
	queryDesc = ExecParallelGetQueryDesc(toc, receiver, instrument_options);

	/* Setting debug_query_string for individual workers */
	debug_query_string = queryDesc->sourceText;

	/* Report workers' query for monitoring purposes */
	pgstat_report_activity(STATE_RUNNING, debug_query_string);

	/* Attach to the dynamic shared memory area. */
	area_space = shm_toc_lookup(toc, PARALLEL_KEY_DSA, false);
	area = dsa_attach_in_place(area_space, seg);

	/* Start up the executor */
	queryDesc->plannedstmt->jitFlags = fpes->jit_flags;
	ExecutorStart(queryDesc, fpes->eflags);

	/* Special executor initialization steps for parallel workers */
	queryDesc->planstate->state->es_query_dsa = area;
	if (DsaPointerIsValid(fpes->param_exec))
	{
		char	   *paramexec_space;

		paramexec_space = dsa_get_address(area, fpes->param_exec);
		RestoreParamExecParams(paramexec_space, queryDesc->estate);

	}
	pwcxt.toc = toc;
	pwcxt.seg = seg;
	ExecParallelInitializeWorker(queryDesc->planstate, &pwcxt);

	/* Pass down any tuple bound */
	ExecSetTupleBound(fpes->tuples_needed, queryDesc->planstate);

	/*
	 * Prepare to track buffer usage during query execution.
	 *
	 * We do this after starting up the executor to match what happens in the
	 * leader, which also doesn't count buffer accesses that occur during
	 * executor startup.
	 */
	InstrStartParallelQuery();

	/*
	 * Run the plan.  If we specified a tuple bound, be careful not to demand
	 * more tuples than that.
	 */
	ExecutorRun(queryDesc,
				ForwardScanDirection,
				fpes->tuples_needed < 0 ? (int64) 0 : fpes->tuples_needed,
				true);

	/* Shut down the executor */
	ExecutorFinish(queryDesc);

	/* Report buffer usage during parallel execution. */
	buffer_usage = shm_toc_lookup(toc, PARALLEL_KEY_BUFFER_USAGE, false);
	InstrEndParallelQuery(&buffer_usage[ParallelWorkerNumber]);

	/* Report instrumentation data if any instrumentation options are set. */
	if (instrumentation != NULL)
		ExecParallelReportInstrumentation(queryDesc->planstate,
										  instrumentation);

	/* Report JIT instrumentation data if any */
	if (queryDesc->estate->es_jit && jit_instrumentation != NULL)
	{
		Assert(ParallelWorkerNumber < jit_instrumentation->num_workers);
		jit_instrumentation->jit_instr[ParallelWorkerNumber] =
			queryDesc->estate->es_jit->instr;
	}

	/* Must do this after capturing instrumentation. */
	ExecutorEnd(queryDesc);

	/* Cleanup. */
	dsa_detach(area);
	FreeQueryDesc(queryDesc);
	receiver->rDestroy(receiver);
}