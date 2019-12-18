#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * printed_subplans; int /*<<< orphan*/  rtable_names; int /*<<< orphan*/  rtable; int /*<<< orphan*/  deparse_cxt; TYPE_1__* pstmt; } ;
struct TYPE_18__ {scalar_t__ invisible; } ;
struct TYPE_17__ {scalar_t__ plan; } ;
struct TYPE_16__ {TYPE_3__* planstate; TYPE_1__* plannedstmt; } ;
struct TYPE_15__ {int /*<<< orphan*/  rtable; } ;
typedef  TYPE_2__ QueryDesc ;
typedef  TYPE_3__ PlanState ;
typedef  TYPE_4__ Gather ;
typedef  TYPE_5__ ExplainState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExplainNode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ExplainPreScanNode (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ExplainPrintSettings (TYPE_5__*) ; 
 int /*<<< orphan*/  GatherState ; 
 scalar_t__ IsA (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  deparse_context_for_plan_rtable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  select_rtable_names_for_explain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ExplainPrintPlan(ExplainState *es, QueryDesc *queryDesc)
{
	Bitmapset  *rels_used = NULL;
	PlanState  *ps;

	/* Set up ExplainState fields associated with this plan tree */
	Assert(queryDesc->plannedstmt != NULL);
	es->pstmt = queryDesc->plannedstmt;
	es->rtable = queryDesc->plannedstmt->rtable;
	ExplainPreScanNode(queryDesc->planstate, &rels_used);
	es->rtable_names = select_rtable_names_for_explain(es->rtable, rels_used);
	es->deparse_cxt = deparse_context_for_plan_rtable(es->rtable,
													  es->rtable_names);
	es->printed_subplans = NULL;

	/*
	 * Sometimes we mark a Gather node as "invisible", which means that it's
	 * not displayed in EXPLAIN output.  The purpose of this is to allow
	 * running regression tests with force_parallel_mode=regress to get the
	 * same results as running the same tests with force_parallel_mode=off.
	 */
	ps = queryDesc->planstate;
	if (IsA(ps, GatherState) &&((Gather *) ps->plan)->invisible)
		ps = outerPlanState(ps);
	ExplainNode(ps, NIL, NULL, NULL, es);

	/*
	 * If requested, include information about GUC parameters with values that
	 * don't match the built-in defaults.
	 */
	ExplainPrintSettings(es);
}