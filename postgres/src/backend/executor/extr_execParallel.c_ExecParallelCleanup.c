#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pcxt; int /*<<< orphan*/ * area; int /*<<< orphan*/  param_exec; scalar_t__ jit_instrumentation; int /*<<< orphan*/  planstate; scalar_t__ instrumentation; } ;
typedef  TYPE_1__ ParallelExecutorInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyParallelContext (int /*<<< orphan*/ *) ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecParallelRetrieveInstrumentation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ExecParallelRetrieveJitInstrumentation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  dsa_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
ExecParallelCleanup(ParallelExecutorInfo *pei)
{
	/* Accumulate instrumentation, if any. */
	if (pei->instrumentation)
		ExecParallelRetrieveInstrumentation(pei->planstate,
											pei->instrumentation);

	/* Accumulate JIT instrumentation, if any. */
	if (pei->jit_instrumentation)
		ExecParallelRetrieveJitInstrumentation(pei->planstate,
											   pei->jit_instrumentation);

	/* Free any serialized parameters. */
	if (DsaPointerIsValid(pei->param_exec))
	{
		dsa_free(pei->area, pei->param_exec);
		pei->param_exec = InvalidDsaPointer;
	}
	if (pei->area != NULL)
	{
		dsa_detach(pei->area);
		pei->area = NULL;
	}
	if (pei->pcxt != NULL)
	{
		DestroyParallelContext(pei->pcxt);
		pei->pcxt = NULL;
	}
	pfree(pei);
}