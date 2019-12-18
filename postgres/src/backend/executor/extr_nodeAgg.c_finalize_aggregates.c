#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* ps_ExprContext; } ;
struct TYPE_18__ {TYPE_1__ ps; } ;
struct TYPE_22__ {int numtrans; scalar_t__ aggstrategy; int numaggs; int /*<<< orphan*/  aggsplit; TYPE_4__* pertrans; TYPE_2__ ss; } ;
struct TYPE_21__ {int transno; } ;
struct TYPE_20__ {scalar_t__ numSortCols; int numInputs; } ;
struct TYPE_19__ {int* ecxt_aggnulls; int /*<<< orphan*/ * ecxt_aggvalues; } ;
typedef  TYPE_3__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__* AggStatePerTrans ;
typedef  int /*<<< orphan*/ * AggStatePerGroup ;
typedef  TYPE_5__* AggStatePerAgg ;
typedef  TYPE_6__ AggState ;

/* Variables and functions */
 scalar_t__ AGG_HASHED ; 
 scalar_t__ AGG_MIXED ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DO_AGGSPLIT_SKIPFINAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_aggregate (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  finalize_partialaggregate (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  process_ordered_aggregate_multi (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_ordered_aggregate_single (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
finalize_aggregates(AggState *aggstate,
					AggStatePerAgg peraggs,
					AggStatePerGroup pergroup)
{
	ExprContext *econtext = aggstate->ss.ps.ps_ExprContext;
	Datum	   *aggvalues = econtext->ecxt_aggvalues;
	bool	   *aggnulls = econtext->ecxt_aggnulls;
	int			aggno;
	int			transno;

	/*
	 * If there were any DISTINCT and/or ORDER BY aggregates, sort their
	 * inputs and run the transition functions.
	 */
	for (transno = 0; transno < aggstate->numtrans; transno++)
	{
		AggStatePerTrans pertrans = &aggstate->pertrans[transno];
		AggStatePerGroup pergroupstate;

		pergroupstate = &pergroup[transno];

		if (pertrans->numSortCols > 0)
		{
			Assert(aggstate->aggstrategy != AGG_HASHED &&
				   aggstate->aggstrategy != AGG_MIXED);

			if (pertrans->numInputs == 1)
				process_ordered_aggregate_single(aggstate,
												 pertrans,
												 pergroupstate);
			else
				process_ordered_aggregate_multi(aggstate,
												pertrans,
												pergroupstate);
		}
	}

	/*
	 * Run the final functions.
	 */
	for (aggno = 0; aggno < aggstate->numaggs; aggno++)
	{
		AggStatePerAgg peragg = &peraggs[aggno];
		int			transno = peragg->transno;
		AggStatePerGroup pergroupstate;

		pergroupstate = &pergroup[transno];

		if (DO_AGGSPLIT_SKIPFINAL(aggstate->aggsplit))
			finalize_partialaggregate(aggstate, peragg, pergroupstate,
									  &aggvalues[aggno], &aggnulls[aggno]);
		else
			finalize_aggregate(aggstate, peragg, pergroupstate,
							   &aggvalues[aggno], &aggnulls[aggno]);
	}
}