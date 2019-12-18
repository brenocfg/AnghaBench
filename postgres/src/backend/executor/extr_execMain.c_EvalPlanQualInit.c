#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int epqParam; int /*<<< orphan*/ * relsubs_done; int /*<<< orphan*/ * relsubs_rowmark; int /*<<< orphan*/ * recheckplanstate; int /*<<< orphan*/ * recheckestate; int /*<<< orphan*/ * origslot; int /*<<< orphan*/ * arowMarks; int /*<<< orphan*/ * plan; int /*<<< orphan*/ ** relsubs_slot; int /*<<< orphan*/  tuple_table; TYPE_1__* parentestate; } ;
struct TYPE_5__ {int es_range_table_size; } ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  List ;
typedef  int Index ;
typedef  TYPE_1__ EState ;
typedef  TYPE_2__ EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 scalar_t__ palloc0 (int) ; 

void
EvalPlanQualInit(EPQState *epqstate, EState *parentestate,
				 Plan *subplan, List *auxrowmarks, int epqParam)
{
	Index		rtsize = parentestate->es_range_table_size;

	/* initialize data not changing over EPQState's lifetime */
	epqstate->parentestate = parentestate;
	epqstate->epqParam = epqParam;

	/*
	 * Allocate space to reference a slot for each potential rti - do so now
	 * rather than in EvalPlanQualBegin(), as done for other dynamically
	 * allocated resources, so EvalPlanQualSlot() can be used to hold tuples
	 * that *may* need EPQ later, without forcing the overhead of
	 * EvalPlanQualBegin().
	 */
	epqstate->tuple_table = NIL;
	epqstate->relsubs_slot = (TupleTableSlot **)
		palloc0(rtsize * sizeof(TupleTableSlot *));

	/* ... and remember data that EvalPlanQualBegin will need */
	epqstate->plan = subplan;
	epqstate->arowMarks = auxrowmarks;

	/* ... and mark the EPQ state inactive */
	epqstate->origslot = NULL;
	epqstate->recheckestate = NULL;
	epqstate->recheckplanstate = NULL;
	epqstate->relsubs_rowmark = NULL;
	epqstate->relsubs_done = NULL;
}