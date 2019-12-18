#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t current_set; TYPE_1__* tmpcontext; } ;
struct TYPE_13__ {int numDistinctCols; int /*<<< orphan*/ ** sortstates; int /*<<< orphan*/  inputtypeByVal; int /*<<< orphan*/  aggCollation; int /*<<< orphan*/  equalfnOne; TYPE_3__* transfn_fcinfo; } ;
struct TYPE_12__ {TYPE_2__* args; } ;
struct TYPE_11__ {scalar_t__ value; int isnull; } ;
struct TYPE_10__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__* FunctionCallInfo ;
typedef  scalar_t__ Datum ;
typedef  TYPE_4__* AggStatePerTrans ;
typedef  int /*<<< orphan*/  AggStatePerGroup ;
typedef  TYPE_5__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advance_transition_function (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_end (int /*<<< orphan*/ *) ; 
 scalar_t__ tuplesort_getdatum (int /*<<< orphan*/ *,int,scalar_t__*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  tuplesort_performsort (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_ordered_aggregate_single(AggState *aggstate,
								 AggStatePerTrans pertrans,
								 AggStatePerGroup pergroupstate)
{
	Datum		oldVal = (Datum) 0;
	bool		oldIsNull = true;
	bool		haveOldVal = false;
	MemoryContext workcontext = aggstate->tmpcontext->ecxt_per_tuple_memory;
	MemoryContext oldContext;
	bool		isDistinct = (pertrans->numDistinctCols > 0);
	Datum		newAbbrevVal = (Datum) 0;
	Datum		oldAbbrevVal = (Datum) 0;
	FunctionCallInfo fcinfo = pertrans->transfn_fcinfo;
	Datum	   *newVal;
	bool	   *isNull;

	Assert(pertrans->numDistinctCols < 2);

	tuplesort_performsort(pertrans->sortstates[aggstate->current_set]);

	/* Load the column into argument 1 (arg 0 will be transition value) */
	newVal = &fcinfo->args[1].value;
	isNull = &fcinfo->args[1].isnull;

	/*
	 * Note: if input type is pass-by-ref, the datums returned by the sort are
	 * freshly palloc'd in the per-query context, so we must be careful to
	 * pfree them when they are no longer needed.
	 */

	while (tuplesort_getdatum(pertrans->sortstates[aggstate->current_set],
							  true, newVal, isNull, &newAbbrevVal))
	{
		/*
		 * Clear and select the working context for evaluation of the equality
		 * function and transition function.
		 */
		MemoryContextReset(workcontext);
		oldContext = MemoryContextSwitchTo(workcontext);

		/*
		 * If DISTINCT mode, and not distinct from prior, skip it.
		 */
		if (isDistinct &&
			haveOldVal &&
			((oldIsNull && *isNull) ||
			 (!oldIsNull && !*isNull &&
			  oldAbbrevVal == newAbbrevVal &&
			  DatumGetBool(FunctionCall2Coll(&pertrans->equalfnOne,
											 pertrans->aggCollation,
											 oldVal, *newVal)))))
		{
			/* equal to prior, so forget this one */
			if (!pertrans->inputtypeByVal && !*isNull)
				pfree(DatumGetPointer(*newVal));
		}
		else
		{
			advance_transition_function(aggstate, pertrans, pergroupstate);
			/* forget the old value, if any */
			if (!oldIsNull && !pertrans->inputtypeByVal)
				pfree(DatumGetPointer(oldVal));
			/* and remember the new one for subsequent equality checks */
			oldVal = *newVal;
			oldAbbrevVal = newAbbrevVal;
			oldIsNull = *isNull;
			haveOldVal = true;
		}

		MemoryContextSwitchTo(oldContext);
	}

	if (!oldIsNull && !pertrans->inputtypeByVal)
		pfree(DatumGetPointer(oldVal));

	tuplesort_end(pertrans->sortstates[aggstate->current_set]);
	pertrans->sortstates[aggstate->current_set] = NULL;
}