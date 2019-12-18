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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ get_negator (scalar_t__) ; 
 int operator_same_subexprs_lookup (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static bool
operator_same_subexprs_proof(Oid pred_op, Oid clause_op, bool refute_it)
{
	/*
	 * A simple and general rule is that the predicate is proven if clause_op
	 * and pred_op are the same, or refuted if they are each other's negators.
	 * We need not check immutability since the pred_op is already known
	 * immutable.  (Actually, by this point we may have the commutator of a
	 * known-immutable pred_op, but that should certainly be immutable too.
	 * Likewise we don't worry whether the pred_op's negator is immutable.)
	 *
	 * Note: the "same" case won't get here if we actually had EXPR1 clause_op
	 * EXPR2 and EXPR1 pred_op EXPR2, because the overall-expression-equality
	 * test in predicate_implied_by_simple_clause would have caught it.  But
	 * we can see the same operator after having commuted the pred_op.
	 */
	if (refute_it)
	{
		if (get_negator(pred_op) == clause_op)
			return true;
	}
	else
	{
		if (pred_op == clause_op)
			return true;
	}

	/*
	 * Otherwise, see if we can determine the implication by finding the
	 * operators' relationship via some btree opfamily.
	 */
	return operator_same_subexprs_lookup(pred_op, clause_op, refute_it);
}