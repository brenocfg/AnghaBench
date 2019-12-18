#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ numSortCols; int numInputs; scalar_t__ transtypeByVal; scalar_t__ initValueIsNull; } ;
struct TYPE_22__ {int setno; int setoff; int transno; int jumpnull; TYPE_10__* aggstate; } ;
struct TYPE_21__ {int setno; int setoff; int transno; int jumpnull; int /*<<< orphan*/ * aggcontext; TYPE_9__* pertrans; TYPE_10__* aggstate; } ;
struct TYPE_20__ {int setno; int setoff; int transno; int /*<<< orphan*/ * aggcontext; TYPE_9__* pertrans; TYPE_10__* aggstate; } ;
struct TYPE_23__ {TYPE_4__ agg_strict_trans_check; TYPE_3__ agg_init_trans; TYPE_2__ agg_trans; } ;
struct TYPE_26__ {TYPE_5__ d; int /*<<< orphan*/  opcode; } ;
struct TYPE_25__ {int steps_len; TYPE_8__* steps; } ;
struct TYPE_24__ {TYPE_1__* flinfo; } ;
struct TYPE_19__ {scalar_t__ fn_strict; } ;
struct TYPE_18__ {int /*<<< orphan*/ ** aggcontexts; int /*<<< orphan*/ * hashcontext; } ;
typedef  TYPE_6__* FunctionCallInfo ;
typedef  TYPE_7__ ExprState ;
typedef  TYPE_8__ ExprEvalStep ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  TYPE_9__* AggStatePerTrans ;
typedef  TYPE_10__ AggState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EEOP_AGG_INIT_TRANS ; 
 int /*<<< orphan*/  EEOP_AGG_ORDERED_TRANS_DATUM ; 
 int /*<<< orphan*/  EEOP_AGG_ORDERED_TRANS_TUPLE ; 
 int /*<<< orphan*/  EEOP_AGG_PLAIN_TRANS ; 
 int /*<<< orphan*/  EEOP_AGG_PLAIN_TRANS_BYVAL ; 
 int /*<<< orphan*/  EEOP_AGG_STRICT_TRANS_CHECK ; 
 int /*<<< orphan*/  ExprEvalPushStep (TYPE_7__*,TYPE_8__*) ; 

__attribute__((used)) static void
ExecBuildAggTransCall(ExprState *state, AggState *aggstate,
					  ExprEvalStep *scratch,
					  FunctionCallInfo fcinfo, AggStatePerTrans pertrans,
					  int transno, int setno, int setoff, bool ishash)
{
	int			adjust_init_jumpnull = -1;
	int			adjust_strict_jumpnull = -1;
	ExprContext *aggcontext;

	if (ishash)
		aggcontext = aggstate->hashcontext;
	else
		aggcontext = aggstate->aggcontexts[setno];

	/*
	 * If the initial value for the transition state doesn't exist in the
	 * pg_aggregate table then we will let the first non-NULL value returned
	 * from the outer procNode become the initial value. (This is useful for
	 * aggregates like max() and min().) The noTransValue flag signals that we
	 * still need to do this.
	 */
	if (pertrans->numSortCols == 0 &&
		fcinfo->flinfo->fn_strict &&
		pertrans->initValueIsNull)
	{
		scratch->opcode = EEOP_AGG_INIT_TRANS;
		scratch->d.agg_init_trans.aggstate = aggstate;
		scratch->d.agg_init_trans.pertrans = pertrans;
		scratch->d.agg_init_trans.setno = setno;
		scratch->d.agg_init_trans.setoff = setoff;
		scratch->d.agg_init_trans.transno = transno;
		scratch->d.agg_init_trans.aggcontext = aggcontext;
		scratch->d.agg_init_trans.jumpnull = -1;	/* adjust later */
		ExprEvalPushStep(state, scratch);

		/* see comment about jumping out below */
		adjust_init_jumpnull = state->steps_len - 1;
	}

	if (pertrans->numSortCols == 0 &&
		fcinfo->flinfo->fn_strict)
	{
		scratch->opcode = EEOP_AGG_STRICT_TRANS_CHECK;
		scratch->d.agg_strict_trans_check.aggstate = aggstate;
		scratch->d.agg_strict_trans_check.setno = setno;
		scratch->d.agg_strict_trans_check.setoff = setoff;
		scratch->d.agg_strict_trans_check.transno = transno;
		scratch->d.agg_strict_trans_check.jumpnull = -1;	/* adjust later */
		ExprEvalPushStep(state, scratch);

		/*
		 * Note, we don't push into adjust_bailout here - those jump to the
		 * end of all transition value computations. Here a single transition
		 * value is NULL, so just skip processing the individual value.
		 */
		adjust_strict_jumpnull = state->steps_len - 1;
	}

	/* invoke appropriate transition implementation */
	if (pertrans->numSortCols == 0 && pertrans->transtypeByVal)
		scratch->opcode = EEOP_AGG_PLAIN_TRANS_BYVAL;
	else if (pertrans->numSortCols == 0)
		scratch->opcode = EEOP_AGG_PLAIN_TRANS;
	else if (pertrans->numInputs == 1)
		scratch->opcode = EEOP_AGG_ORDERED_TRANS_DATUM;
	else
		scratch->opcode = EEOP_AGG_ORDERED_TRANS_TUPLE;

	scratch->d.agg_trans.aggstate = aggstate;
	scratch->d.agg_trans.pertrans = pertrans;
	scratch->d.agg_trans.setno = setno;
	scratch->d.agg_trans.setoff = setoff;
	scratch->d.agg_trans.transno = transno;
	scratch->d.agg_trans.aggcontext = aggcontext;
	ExprEvalPushStep(state, scratch);

	/* adjust jumps so they jump till after transition invocation */
	if (adjust_init_jumpnull != -1)
	{
		ExprEvalStep *as = &state->steps[adjust_init_jumpnull];

		Assert(as->d.agg_init_trans.jumpnull == -1);
		as->d.agg_init_trans.jumpnull = state->steps_len;
	}
	if (adjust_strict_jumpnull != -1)
	{
		ExprEvalStep *as = &state->steps[adjust_strict_jumpnull];

		Assert(as->d.agg_strict_trans_check.jumpnull == -1);
		as->d.agg_strict_trans_check.jumpnull = state->steps_len;
	}
}