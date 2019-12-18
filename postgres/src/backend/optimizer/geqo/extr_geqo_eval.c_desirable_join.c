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
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 scalar_t__ have_join_order_restriction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ have_relevant_joinclause (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
desirable_join(PlannerInfo *root,
			   RelOptInfo *outer_rel, RelOptInfo *inner_rel)
{
	/*
	 * Join if there is an applicable join clause, or if there is a join order
	 * restriction forcing these rels to be joined.
	 */
	if (have_relevant_joinclause(root, outer_rel, inner_rel) ||
		have_join_order_restriction(root, outer_rel, inner_rel))
		return true;

	/* Otherwise postpone the join till later. */
	return false;
}