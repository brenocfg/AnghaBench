#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  contains_outer; } ;
typedef  TYPE_2__ reduce_outer_joins_state ;
struct TYPE_10__ {TYPE_1__* parse; } ;
struct TYPE_8__ {scalar_t__ jointree; } ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* reduce_outer_joins_pass1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reduce_outer_joins_pass2 (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
reduce_outer_joins(PlannerInfo *root)
{
	reduce_outer_joins_state *state;

	/*
	 * To avoid doing strictness checks on more quals than necessary, we want
	 * to stop descending the jointree as soon as there are no outer joins
	 * below our current point.  This consideration forces a two-pass process.
	 * The first pass gathers information about which base rels appear below
	 * each side of each join clause, and about whether there are outer
	 * join(s) below each side of each join clause. The second pass examines
	 * qual clauses and changes join types as it descends the tree.
	 */
	state = reduce_outer_joins_pass1((Node *) root->parse->jointree);

	/* planner.c shouldn't have called me if no outer joins */
	if (state == NULL || !state->contains_outer)
		elog(ERROR, "so where are the outer joins?");

	reduce_outer_joins_pass2((Node *) root->parse->jointree,
							 state, root, NULL, NIL, NIL);
}