#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ ec_broken; int /*<<< orphan*/  ec_relids; int /*<<< orphan*/  ec_members; scalar_t__ ec_has_const; } ;
struct TYPE_14__ {int /*<<< orphan*/  eq_classes; } ;
struct TYPE_13__ {int /*<<< orphan*/  relids; int /*<<< orphan*/  top_parent_relids; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ EquivalenceClass ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IS_OTHER_REL (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int bms_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * generate_join_implied_equalities_broken (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * generate_join_implied_equalities_normal (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_common_eclass_indexes (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 

List *
generate_join_implied_equalities(PlannerInfo *root,
								 Relids join_relids,
								 Relids outer_relids,
								 RelOptInfo *inner_rel)
{
	List	   *result = NIL;
	Relids		inner_relids = inner_rel->relids;
	Relids		nominal_inner_relids;
	Relids		nominal_join_relids;
	Bitmapset  *matching_ecs;
	int			i;

	/* If inner rel is a child, extra setup work is needed */
	if (IS_OTHER_REL(inner_rel))
	{
		Assert(!bms_is_empty(inner_rel->top_parent_relids));

		/* Fetch relid set for the topmost parent rel */
		nominal_inner_relids = inner_rel->top_parent_relids;
		/* ECs will be marked with the parent's relid, not the child's */
		nominal_join_relids = bms_union(outer_relids, nominal_inner_relids);
	}
	else
	{
		nominal_inner_relids = inner_relids;
		nominal_join_relids = join_relids;
	}

	/*
	 * Get all eclasses in common between inner_rel's relids and outer_relids
	 */
	matching_ecs = get_common_eclass_indexes(root, inner_rel->relids,
											 outer_relids);

	i = -1;
	while ((i = bms_next_member(matching_ecs, i)) >= 0)
	{
		EquivalenceClass *ec = (EquivalenceClass *) list_nth(root->eq_classes, i);
		List	   *sublist = NIL;

		/* ECs containing consts do not need any further enforcement */
		if (ec->ec_has_const)
			continue;

		/* Single-member ECs won't generate any deductions */
		if (list_length(ec->ec_members) <= 1)
			continue;

		/* Sanity check that this eclass overlaps the join */
		Assert(bms_overlap(ec->ec_relids, nominal_join_relids));

		if (!ec->ec_broken)
			sublist = generate_join_implied_equalities_normal(root,
															  ec,
															  join_relids,
															  outer_relids,
															  inner_relids);

		/* Recover if we failed to generate required derived clauses */
		if (ec->ec_broken)
			sublist = generate_join_implied_equalities_broken(root,
															  ec,
															  nominal_join_relids,
															  outer_relids,
															  nominal_inner_relids,
															  inner_rel);

		result = list_concat(result, sublist);
	}

	return result;
}