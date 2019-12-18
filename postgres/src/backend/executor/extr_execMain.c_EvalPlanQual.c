#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  EvalPlanQualBegin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EvalPlanQualNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EvalPlanQualSlot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TupIsNull (int /*<<< orphan*/ *) ; 

TupleTableSlot *
EvalPlanQual(EPQState *epqstate, Relation relation,
			 Index rti, TupleTableSlot *inputslot)
{
	TupleTableSlot *slot;
	TupleTableSlot *testslot;

	Assert(rti > 0);

	/*
	 * Need to run a recheck subquery.  Initialize or reinitialize EPQ state.
	 */
	EvalPlanQualBegin(epqstate);

	/*
	 * Callers will often use the EvalPlanQualSlot to store the tuple to avoid
	 * an unnecessary copy.
	 */
	testslot = EvalPlanQualSlot(epqstate, relation, rti);
	if (testslot != inputslot)
		ExecCopySlot(testslot, inputslot);

	/*
	 * Run the EPQ query.  We assume it will return at most one tuple.
	 */
	slot = EvalPlanQualNext(epqstate);

	/*
	 * If we got a tuple, force the slot to materialize the tuple so that it
	 * is not dependent on any local state in the EPQ query (in particular,
	 * it's highly likely that the slot contains references to any pass-by-ref
	 * datums that may be present in copyTuple).  As with the next step, this
	 * is to guard against early re-use of the EPQ query.
	 */
	if (!TupIsNull(slot))
		ExecMaterializeSlot(slot);

	/*
	 * Clear out the test tuple.  This is needed in case the EPQ query is
	 * re-used to test a tuple for a different relation.  (Not clear that can
	 * really happen, but let's be safe.)
	 */
	ExecClearTuple(testslot);

	return slot;
}