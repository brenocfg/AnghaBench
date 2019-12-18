#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* parse; } ;
struct TYPE_7__ {scalar_t__ rtekind; scalar_t__ values_lists; } ;
struct TYPE_6__ {scalar_t__ rtable; } ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RTE_VALUES ; 
 scalar_t__ contain_volatile_functions (int /*<<< orphan*/ *) ; 
 scalar_t__ expression_returns_set (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (scalar_t__) ; 
 int list_length (scalar_t__) ; 

__attribute__((used)) static bool
is_simple_values(PlannerInfo *root, RangeTblEntry *rte)
{
	Assert(rte->rtekind == RTE_VALUES);

	/*
	 * There must be exactly one VALUES list, else it's not semantically
	 * correct to replace the VALUES RTE with a RESULT RTE, nor would we have
	 * a unique set of expressions to substitute into the parent query.
	 */
	if (list_length(rte->values_lists) != 1)
		return false;

	/*
	 * Because VALUES can't appear under an outer join (or at least, we won't
	 * try to pull it up if it does), we need not worry about LATERAL, nor
	 * about validity of PHVs for the VALUES' outputs.
	 */

	/*
	 * Don't pull up a VALUES that contains any set-returning or volatile
	 * functions.  The considerations here are basically identical to the
	 * restrictions on a pull-able subquery's targetlist.
	 */
	if (expression_returns_set((Node *) rte->values_lists) ||
		contain_volatile_functions((Node *) rte->values_lists))
		return false;

	/*
	 * Do not pull up a VALUES that's not the only RTE in its parent query.
	 * This is actually the only case that the parser will generate at the
	 * moment, and assuming this is true greatly simplifies
	 * pull_up_simple_values().
	 */
	if (list_length(root->parse->rtable) != 1 ||
		rte != (RangeTblEntry *) linitial(root->parse->rtable))
		return false;

	return true;
}