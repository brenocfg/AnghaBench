#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  relids; } ;
struct TYPE_18__ {int lhs_strict; int delay_upper_joins; int semi_can_btree; int semi_can_hash; void* semi_rhs_exprs; void* semi_operators; int /*<<< orphan*/  jointype; int /*<<< orphan*/  syn_righthand; int /*<<< orphan*/  syn_lefthand; int /*<<< orphan*/  min_righthand; int /*<<< orphan*/  min_lefthand; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SpecialJoinInfo ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JOIN_INNER ; 
 void* NIL ; 
 int /*<<< orphan*/  T_SpecialJoinInfo ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* build_join_rel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ is_dummy_rel (TYPE_2__*) ; 
 int /*<<< orphan*/  join_is_legal (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**,int*) ; 
 int /*<<< orphan*/  populate_joinrel_with_paths (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

RelOptInfo *
make_join_rel(PlannerInfo *root, RelOptInfo *rel1, RelOptInfo *rel2)
{
	Relids		joinrelids;
	SpecialJoinInfo *sjinfo;
	bool		reversed;
	SpecialJoinInfo sjinfo_data;
	RelOptInfo *joinrel;
	List	   *restrictlist;

	/* We should never try to join two overlapping sets of rels. */
	Assert(!bms_overlap(rel1->relids, rel2->relids));

	/* Construct Relids set that identifies the joinrel. */
	joinrelids = bms_union(rel1->relids, rel2->relids);

	/* Check validity and determine join type. */
	if (!join_is_legal(root, rel1, rel2, joinrelids,
					   &sjinfo, &reversed))
	{
		/* invalid join path */
		bms_free(joinrelids);
		return NULL;
	}

	/* Swap rels if needed to match the join info. */
	if (reversed)
	{
		RelOptInfo *trel = rel1;

		rel1 = rel2;
		rel2 = trel;
	}

	/*
	 * If it's a plain inner join, then we won't have found anything in
	 * join_info_list.  Make up a SpecialJoinInfo so that selectivity
	 * estimation functions will know what's being joined.
	 */
	if (sjinfo == NULL)
	{
		sjinfo = &sjinfo_data;
		sjinfo->type = T_SpecialJoinInfo;
		sjinfo->min_lefthand = rel1->relids;
		sjinfo->min_righthand = rel2->relids;
		sjinfo->syn_lefthand = rel1->relids;
		sjinfo->syn_righthand = rel2->relids;
		sjinfo->jointype = JOIN_INNER;
		/* we don't bother trying to make the remaining fields valid */
		sjinfo->lhs_strict = false;
		sjinfo->delay_upper_joins = false;
		sjinfo->semi_can_btree = false;
		sjinfo->semi_can_hash = false;
		sjinfo->semi_operators = NIL;
		sjinfo->semi_rhs_exprs = NIL;
	}

	/*
	 * Find or build the join RelOptInfo, and compute the restrictlist that
	 * goes with this particular joining.
	 */
	joinrel = build_join_rel(root, joinrelids, rel1, rel2, sjinfo,
							 &restrictlist);

	/*
	 * If we've already proven this join is empty, we needn't consider any
	 * more paths for it.
	 */
	if (is_dummy_rel(joinrel))
	{
		bms_free(joinrelids);
		return joinrel;
	}

	/* Add paths to the join relation. */
	populate_joinrel_with_paths(root, rel1, rel2, joinrel, sjinfo,
								restrictlist);

	bms_free(joinrelids);

	return joinrel;
}