#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_2__* estate; } ;
struct TYPE_9__ {int es_jit_flags; int /*<<< orphan*/ * es_jit_worker_instr; TYPE_1__* es_jit; } ;
struct TYPE_8__ {int /*<<< orphan*/  instr; } ;
typedef  TYPE_3__ QueryDesc ;
typedef  TYPE_4__ JitInstrumentation ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainPrintJIT (int /*<<< orphan*/ *,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  InstrJitAgg (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int PGJIT_PERFORM ; 

void
ExplainPrintJITSummary(ExplainState *es, QueryDesc *queryDesc)
{
	JitInstrumentation ji = {0};

	if (!(queryDesc->estate->es_jit_flags & PGJIT_PERFORM))
		return;

	/*
	 * Work with a copy instead of modifying the leader state, since this
	 * function may be called twice
	 */
	if (queryDesc->estate->es_jit)
		InstrJitAgg(&ji, &queryDesc->estate->es_jit->instr);

	/* If this process has done JIT in parallel workers, merge stats */
	if (queryDesc->estate->es_jit_worker_instr)
		InstrJitAgg(&ji, queryDesc->estate->es_jit_worker_instr);

	ExplainPrintJIT(es, queryDesc->estate->es_jit_flags, &ji, -1);
}