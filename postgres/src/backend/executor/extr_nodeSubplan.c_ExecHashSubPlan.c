#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_10__ {int /*<<< orphan*/ * pi_exprContext; } ;
struct TYPE_9__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_8__ {scalar_t__ parParam; } ;
struct TYPE_7__ {scalar_t__ args; int /*<<< orphan*/  cur_eq_funcs; int /*<<< orphan*/ * hashtable; scalar_t__ havehashrows; int /*<<< orphan*/ * hashnulls; scalar_t__ havenullrows; int /*<<< orphan*/  lhs_hash_funcs; int /*<<< orphan*/  cur_eq_comp; TYPE_5__* projLeft; TYPE_3__* planstate; TYPE_2__* subplan; } ;
typedef  TYPE_1__ SubPlanState ;
typedef  TYPE_2__ SubPlan ;
typedef  TYPE_3__ PlanState ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProject (TYPE_5__*) ; 
 int /*<<< orphan*/ * FindTupleHashEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  buildSubPlanHash (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ findPartialMatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ slotAllNulls (int /*<<< orphan*/ *) ; 
 scalar_t__ slotNoNulls (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Datum
ExecHashSubPlan(SubPlanState *node,
				ExprContext *econtext,
				bool *isNull)
{
	SubPlan    *subplan = node->subplan;
	PlanState  *planstate = node->planstate;
	TupleTableSlot *slot;

	/* Shouldn't have any direct correlation Vars */
	if (subplan->parParam != NIL || node->args != NIL)
		elog(ERROR, "hashed subplan with direct correlation not supported");

	/*
	 * If first time through or we need to rescan the subplan, build the hash
	 * table.
	 */
	if (node->hashtable == NULL || planstate->chgParam != NULL)
		buildSubPlanHash(node, econtext);

	/*
	 * The result for an empty subplan is always FALSE; no need to evaluate
	 * lefthand side.
	 */
	*isNull = false;
	if (!node->havehashrows && !node->havenullrows)
		return BoolGetDatum(false);

	/*
	 * Evaluate lefthand expressions and form a projection tuple. First we
	 * have to set the econtext to use (hack alert!).
	 */
	node->projLeft->pi_exprContext = econtext;
	slot = ExecProject(node->projLeft);

	/*
	 * Note: because we are typically called in a per-tuple context, we have
	 * to explicitly clear the projected tuple before returning. Otherwise,
	 * we'll have a double-free situation: the per-tuple context will probably
	 * be reset before we're called again, and then the tuple slot will think
	 * it still needs to free the tuple.
	 */

	/*
	 * If the LHS is all non-null, probe for an exact match in the main hash
	 * table.  If we find one, the result is TRUE. Otherwise, scan the
	 * partly-null table to see if there are any rows that aren't provably
	 * unequal to the LHS; if so, the result is UNKNOWN.  (We skip that part
	 * if we don't care about UNKNOWN.) Otherwise, the result is FALSE.
	 *
	 * Note: the reason we can avoid a full scan of the main hash table is
	 * that the combining operators are assumed never to yield NULL when both
	 * inputs are non-null.  If they were to do so, we might need to produce
	 * UNKNOWN instead of FALSE because of an UNKNOWN result in comparing the
	 * LHS to some main-table entry --- which is a comparison we will not even
	 * make, unless there's a chance match of hash keys.
	 */
	if (slotNoNulls(slot))
	{
		if (node->havehashrows &&
			FindTupleHashEntry(node->hashtable,
							   slot,
							   node->cur_eq_comp,
							   node->lhs_hash_funcs) != NULL)
		{
			ExecClearTuple(slot);
			return BoolGetDatum(true);
		}
		if (node->havenullrows &&
			findPartialMatch(node->hashnulls, slot, node->cur_eq_funcs))
		{
			ExecClearTuple(slot);
			*isNull = true;
			return BoolGetDatum(false);
		}
		ExecClearTuple(slot);
		return BoolGetDatum(false);
	}

	/*
	 * When the LHS is partly or wholly NULL, we can never return TRUE. If we
	 * don't care about UNKNOWN, just return FALSE.  Otherwise, if the LHS is
	 * wholly NULL, immediately return UNKNOWN.  (Since the combining
	 * operators are strict, the result could only be FALSE if the sub-select
	 * were empty, but we already handled that case.) Otherwise, we must scan
	 * both the main and partly-null tables to see if there are any rows that
	 * aren't provably unequal to the LHS; if so, the result is UNKNOWN.
	 * Otherwise, the result is FALSE.
	 */
	if (node->hashnulls == NULL)
	{
		ExecClearTuple(slot);
		return BoolGetDatum(false);
	}
	if (slotAllNulls(slot))
	{
		ExecClearTuple(slot);
		*isNull = true;
		return BoolGetDatum(false);
	}
	/* Scan partly-null table first, since more likely to get a match */
	if (node->havenullrows &&
		findPartialMatch(node->hashnulls, slot, node->cur_eq_funcs))
	{
		ExecClearTuple(slot);
		*isNull = true;
		return BoolGetDatum(false);
	}
	if (node->havehashrows &&
		findPartialMatch(node->hashtable, slot, node->cur_eq_funcs))
	{
		ExecClearTuple(slot);
		*isNull = true;
		return BoolGetDatum(false);
	}
	ExecClearTuple(slot);
	return BoolGetDatum(false);
}