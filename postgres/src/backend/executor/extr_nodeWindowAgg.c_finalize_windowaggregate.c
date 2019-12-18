#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_6__* WindowStatePerFunc ;
typedef  TYPE_7__* WindowStatePerAgg ;
struct TYPE_19__ {TYPE_1__* ps_ExprContext; } ;
struct TYPE_20__ {TYPE_2__ ps; } ;
struct TYPE_25__ {int /*<<< orphan*/ * curaggcontext; TYPE_3__ ss; } ;
typedef  TYPE_8__ WindowAggState ;
struct TYPE_24__ {int numFinalArgs; int transValueIsNull; int /*<<< orphan*/  resulttypeLen; int /*<<< orphan*/  resulttypeByVal; scalar_t__ transValue; int /*<<< orphan*/ * aggcontext; int /*<<< orphan*/  transtypeLen; int /*<<< orphan*/  finalfn; int /*<<< orphan*/  finalfn_oid; } ;
struct TYPE_23__ {int /*<<< orphan*/  winCollation; } ;
struct TYPE_22__ {scalar_t__ fn_strict; } ;
struct TYPE_21__ {int isnull; scalar_t__ value; } ;
struct TYPE_18__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_17__ {int isnull; TYPE_5__* flinfo; TYPE_4__* args; } ;
struct TYPE_16__ {int /*<<< orphan*/  fcinfo; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  FUNC_MAX_ARGS ; 
 scalar_t__ FunctionCallInvoke (TYPE_13__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_13__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MakeExpandedObjectReadOnly (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextContains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ datumCopy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* fcinfo ; 
 TYPE_12__ fcinfodata ; 

__attribute__((used)) static void
finalize_windowaggregate(WindowAggState *winstate,
						 WindowStatePerFunc perfuncstate,
						 WindowStatePerAgg peraggstate,
						 Datum *result, bool *isnull)
{
	MemoryContext oldContext;

	oldContext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_tuple_memory);

	/*
	 * Apply the agg's finalfn if one is provided, else return transValue.
	 */
	if (OidIsValid(peraggstate->finalfn_oid))
	{
		LOCAL_FCINFO(fcinfo, FUNC_MAX_ARGS);
		int			numFinalArgs = peraggstate->numFinalArgs;
		bool		anynull;
		int			i;

		InitFunctionCallInfoData(fcinfodata.fcinfo, &(peraggstate->finalfn),
								 numFinalArgs,
								 perfuncstate->winCollation,
								 (void *) winstate, NULL);
		fcinfo->args[0].value =
			MakeExpandedObjectReadOnly(peraggstate->transValue,
									   peraggstate->transValueIsNull,
									   peraggstate->transtypeLen);
		fcinfo->args[0].isnull = peraggstate->transValueIsNull;
		anynull = peraggstate->transValueIsNull;

		/* Fill any remaining argument positions with nulls */
		for (i = 1; i < numFinalArgs; i++)
		{
			fcinfo->args[i].value = (Datum) 0;
			fcinfo->args[i].isnull = true;
			anynull = true;
		}

		if (fcinfo->flinfo->fn_strict && anynull)
		{
			/* don't call a strict function with NULL inputs */
			*result = (Datum) 0;
			*isnull = true;
		}
		else
		{
			winstate->curaggcontext = peraggstate->aggcontext;
			*result = FunctionCallInvoke(fcinfo);
			winstate->curaggcontext = NULL;
			*isnull = fcinfo->isnull;
		}
	}
	else
	{
		/* Don't need MakeExpandedObjectReadOnly; datumCopy will copy it */
		*result = peraggstate->transValue;
		*isnull = peraggstate->transValueIsNull;
	}

	/*
	 * If result is pass-by-ref, make sure it is in the right context.
	 */
	if (!peraggstate->resulttypeByVal && !*isnull &&
		!MemoryContextContains(CurrentMemoryContext,
							   DatumGetPointer(*result)))
		*result = datumCopy(*result,
							peraggstate->resulttypeByVal,
							peraggstate->resulttypeLen);
	MemoryContextSwitchTo(oldContext);
}