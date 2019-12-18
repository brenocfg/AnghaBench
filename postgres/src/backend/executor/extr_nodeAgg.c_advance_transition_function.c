#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_4__* curaggcontext; TYPE_6__* curpertrans; TYPE_2__* tmpcontext; } ;
struct TYPE_21__ {int noTransValue; int transValueIsNull; void* transValue; } ;
struct TYPE_15__ {scalar_t__ fn_strict; } ;
struct TYPE_20__ {int numTransInputs; int /*<<< orphan*/  transtypeLen; int /*<<< orphan*/  transtypeByVal; TYPE_1__ transfn; TYPE_5__* transfn_fcinfo; } ;
struct TYPE_19__ {int isnull; TYPE_3__* args; } ;
struct TYPE_18__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_17__ {int isnull; void* value; } ;
struct TYPE_16__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_14__ {int /*<<< orphan*/  eoh_context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_5__* FunctionCallInfo ;
typedef  void* Datum ;
typedef  TYPE_6__* AggStatePerTrans ;
typedef  TYPE_7__* AggStatePerGroup ;
typedef  TYPE_8__ AggState ;

/* Variables and functions */
 scalar_t__ CurrentMemoryContext ; 
 TYPE_13__* DatumGetEOHP (void*) ; 
 scalar_t__ DatumGetPointer (void*) ; 
 scalar_t__ DatumIsReadWriteExpandedObject (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteExpandedObject (void*) ; 
 void* FunctionCallInvoke (TYPE_5__*) ; 
 scalar_t__ MemoryContextGetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 void* datumCopy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static void
advance_transition_function(AggState *aggstate,
							AggStatePerTrans pertrans,
							AggStatePerGroup pergroupstate)
{
	FunctionCallInfo fcinfo = pertrans->transfn_fcinfo;
	MemoryContext oldContext;
	Datum		newVal;

	if (pertrans->transfn.fn_strict)
	{
		/*
		 * For a strict transfn, nothing happens when there's a NULL input; we
		 * just keep the prior transValue.
		 */
		int			numTransInputs = pertrans->numTransInputs;
		int			i;

		for (i = 1; i <= numTransInputs; i++)
		{
			if (fcinfo->args[i].isnull)
				return;
		}
		if (pergroupstate->noTransValue)
		{
			/*
			 * transValue has not been initialized. This is the first non-NULL
			 * input value. We use it as the initial value for transValue. (We
			 * already checked that the agg's input type is binary-compatible
			 * with its transtype, so straight copy here is OK.)
			 *
			 * We must copy the datum into aggcontext if it is pass-by-ref. We
			 * do not need to pfree the old transValue, since it's NULL.
			 */
			oldContext = MemoryContextSwitchTo(
											   aggstate->curaggcontext->ecxt_per_tuple_memory);
			pergroupstate->transValue = datumCopy(fcinfo->args[1].value,
												  pertrans->transtypeByVal,
												  pertrans->transtypeLen);
			pergroupstate->transValueIsNull = false;
			pergroupstate->noTransValue = false;
			MemoryContextSwitchTo(oldContext);
			return;
		}
		if (pergroupstate->transValueIsNull)
		{
			/*
			 * Don't call a strict function with NULL inputs.  Note it is
			 * possible to get here despite the above tests, if the transfn is
			 * strict *and* returned a NULL on a prior cycle. If that happens
			 * we will propagate the NULL all the way to the end.
			 */
			return;
		}
	}

	/* We run the transition functions in per-input-tuple memory context */
	oldContext = MemoryContextSwitchTo(aggstate->tmpcontext->ecxt_per_tuple_memory);

	/* set up aggstate->curpertrans for AggGetAggref() */
	aggstate->curpertrans = pertrans;

	/*
	 * OK to call the transition function
	 */
	fcinfo->args[0].value = pergroupstate->transValue;
	fcinfo->args[0].isnull = pergroupstate->transValueIsNull;
	fcinfo->isnull = false;		/* just in case transfn doesn't set it */

	newVal = FunctionCallInvoke(fcinfo);

	aggstate->curpertrans = NULL;

	/*
	 * If pass-by-ref datatype, must copy the new value into aggcontext and
	 * free the prior transValue.  But if transfn returned a pointer to its
	 * first input, we don't need to do anything.  Also, if transfn returned a
	 * pointer to a R/W expanded object that is already a child of the
	 * aggcontext, assume we can adopt that value without copying it.
	 */
	if (!pertrans->transtypeByVal &&
		DatumGetPointer(newVal) != DatumGetPointer(pergroupstate->transValue))
	{
		if (!fcinfo->isnull)
		{
			MemoryContextSwitchTo(aggstate->curaggcontext->ecxt_per_tuple_memory);
			if (DatumIsReadWriteExpandedObject(newVal,
											   false,
											   pertrans->transtypeLen) &&
				MemoryContextGetParent(DatumGetEOHP(newVal)->eoh_context) == CurrentMemoryContext)
				 /* do nothing */ ;
			else
				newVal = datumCopy(newVal,
								   pertrans->transtypeByVal,
								   pertrans->transtypeLen);
		}
		if (!pergroupstate->transValueIsNull)
		{
			if (DatumIsReadWriteExpandedObject(pergroupstate->transValue,
											   false,
											   pertrans->transtypeLen))
				DeleteExpandedObject(pergroupstate->transValue);
			else
				pfree(DatumGetPointer(pergroupstate->transValue));
		}
	}

	pergroupstate->transValue = newVal;
	pergroupstate->transValueIsNull = fcinfo->isnull;

	MemoryContextSwitchTo(oldContext);
}