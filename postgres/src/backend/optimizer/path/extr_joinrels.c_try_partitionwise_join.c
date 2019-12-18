#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int consider_partitionwise_join; int nparts; scalar_t__ reloptkind; int /*<<< orphan*/  relids; struct TYPE_25__** part_rels; int /*<<< orphan*/  boundinfo; TYPE_1__* part_scheme; } ;
struct TYPE_24__ {int jointype; } ;
struct TYPE_23__ {int /*<<< orphan*/  parttypbyval; int /*<<< orphan*/  parttyplen; int /*<<< orphan*/  partnatts; } ;
typedef  TYPE_2__ SpecialJoinInfo ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_3__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int IS_DUMMY_REL (TYPE_3__*) ; 
 scalar_t__ IS_PARTITIONED_REL (TYPE_3__*) ; 
 int IS_SIMPLE_REL (TYPE_3__*) ; 
#define  JOIN_ANTI 132 
#define  JOIN_FULL 131 
#define  JOIN_INNER 130 
#define  JOIN_LEFT 129 
#define  JOIN_SEMI 128 
 scalar_t__ RELOPT_OTHER_MEMBER_REL ; 
 scalar_t__ REL_HAS_ALL_PART_PROPS (TYPE_3__*) ; 
 scalar_t__ adjust_appendrel_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int bms_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* build_child_join_rel (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 TYPE_2__* build_child_join_sjinfo (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ ** find_appinfos_by_relids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int partition_bounds_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  populate_joinrel_with_paths (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
try_partitionwise_join(PlannerInfo *root, RelOptInfo *rel1, RelOptInfo *rel2,
					   RelOptInfo *joinrel, SpecialJoinInfo *parent_sjinfo,
					   List *parent_restrictlist)
{
	bool		rel1_is_simple = IS_SIMPLE_REL(rel1);
	bool		rel2_is_simple = IS_SIMPLE_REL(rel2);
	int			nparts;
	int			cnt_parts;

	/* Guard against stack overflow due to overly deep partition hierarchy. */
	check_stack_depth();

	/* Nothing to do, if the join relation is not partitioned. */
	if (!IS_PARTITIONED_REL(joinrel))
		return;

	/* The join relation should have consider_partitionwise_join set. */
	Assert(joinrel->consider_partitionwise_join);

	/*
	 * Since this join relation is partitioned, all the base relations
	 * participating in this join must be partitioned and so are all the
	 * intermediate join relations.
	 */
	Assert(IS_PARTITIONED_REL(rel1) && IS_PARTITIONED_REL(rel2));
	Assert(REL_HAS_ALL_PART_PROPS(rel1) && REL_HAS_ALL_PART_PROPS(rel2));

	/* The joining relations should have consider_partitionwise_join set. */
	Assert(rel1->consider_partitionwise_join &&
		   rel2->consider_partitionwise_join);

	/*
	 * The partition scheme of the join relation should match that of the
	 * joining relations.
	 */
	Assert(joinrel->part_scheme == rel1->part_scheme &&
		   joinrel->part_scheme == rel2->part_scheme);

	/*
	 * Since we allow partitionwise join only when the partition bounds of the
	 * joining relations exactly match, the partition bounds of the join
	 * should match those of the joining relations.
	 */
	Assert(partition_bounds_equal(joinrel->part_scheme->partnatts,
								  joinrel->part_scheme->parttyplen,
								  joinrel->part_scheme->parttypbyval,
								  joinrel->boundinfo, rel1->boundinfo));
	Assert(partition_bounds_equal(joinrel->part_scheme->partnatts,
								  joinrel->part_scheme->parttyplen,
								  joinrel->part_scheme->parttypbyval,
								  joinrel->boundinfo, rel2->boundinfo));

	nparts = joinrel->nparts;

	/*
	 * Create child-join relations for this partitioned join, if those don't
	 * exist. Add paths to child-joins for a pair of child relations
	 * corresponding to the given pair of parent relations.
	 */
	for (cnt_parts = 0; cnt_parts < nparts; cnt_parts++)
	{
		RelOptInfo *child_rel1 = rel1->part_rels[cnt_parts];
		RelOptInfo *child_rel2 = rel2->part_rels[cnt_parts];
		bool		rel1_empty = (child_rel1 == NULL ||
								  IS_DUMMY_REL(child_rel1));
		bool		rel2_empty = (child_rel2 == NULL ||
								  IS_DUMMY_REL(child_rel2));
		SpecialJoinInfo *child_sjinfo;
		List	   *child_restrictlist;
		RelOptInfo *child_joinrel;
		Relids		child_joinrelids;
		AppendRelInfo **appinfos;
		int			nappinfos;

		/*
		 * Check for cases where we can prove that this segment of the join
		 * returns no rows, due to one or both inputs being empty (including
		 * inputs that have been pruned away entirely).  If so just ignore it.
		 * These rules are equivalent to populate_joinrel_with_paths's rules
		 * for dummy input relations.
		 */
		switch (parent_sjinfo->jointype)
		{
			case JOIN_INNER:
			case JOIN_SEMI:
				if (rel1_empty || rel2_empty)
					continue;	/* ignore this join segment */
				break;
			case JOIN_LEFT:
			case JOIN_ANTI:
				if (rel1_empty)
					continue;	/* ignore this join segment */
				break;
			case JOIN_FULL:
				if (rel1_empty && rel2_empty)
					continue;	/* ignore this join segment */
				break;
			default:
				/* other values not expected here */
				elog(ERROR, "unrecognized join type: %d",
					 (int) parent_sjinfo->jointype);
				break;
		}

		/*
		 * If a child has been pruned entirely then we can't generate paths
		 * for it, so we have to reject partitionwise joining unless we were
		 * able to eliminate this partition above.
		 */
		if (child_rel1 == NULL || child_rel2 == NULL)
		{
			/*
			 * Mark the joinrel as unpartitioned so that later functions treat
			 * it correctly.
			 */
			joinrel->nparts = 0;
			return;
		}

		/*
		 * If a leaf relation has consider_partitionwise_join=false, it means
		 * that it's a dummy relation for which we skipped setting up tlist
		 * expressions and adding EC members in set_append_rel_size(), so
		 * again we have to fail here.
		 */
		if (rel1_is_simple && !child_rel1->consider_partitionwise_join)
		{
			Assert(child_rel1->reloptkind == RELOPT_OTHER_MEMBER_REL);
			Assert(IS_DUMMY_REL(child_rel1));
			joinrel->nparts = 0;
			return;
		}
		if (rel2_is_simple && !child_rel2->consider_partitionwise_join)
		{
			Assert(child_rel2->reloptkind == RELOPT_OTHER_MEMBER_REL);
			Assert(IS_DUMMY_REL(child_rel2));
			joinrel->nparts = 0;
			return;
		}

		/* We should never try to join two overlapping sets of rels. */
		Assert(!bms_overlap(child_rel1->relids, child_rel2->relids));
		child_joinrelids = bms_union(child_rel1->relids, child_rel2->relids);
		appinfos = find_appinfos_by_relids(root, child_joinrelids, &nappinfos);

		/*
		 * Construct SpecialJoinInfo from parent join relations's
		 * SpecialJoinInfo.
		 */
		child_sjinfo = build_child_join_sjinfo(root, parent_sjinfo,
											   child_rel1->relids,
											   child_rel2->relids);

		/*
		 * Construct restrictions applicable to the child join from those
		 * applicable to the parent join.
		 */
		child_restrictlist =
			(List *) adjust_appendrel_attrs(root,
											(Node *) parent_restrictlist,
											nappinfos, appinfos);
		pfree(appinfos);

		child_joinrel = joinrel->part_rels[cnt_parts];
		if (!child_joinrel)
		{
			child_joinrel = build_child_join_rel(root, child_rel1, child_rel2,
												 joinrel, child_restrictlist,
												 child_sjinfo,
												 child_sjinfo->jointype);
			joinrel->part_rels[cnt_parts] = child_joinrel;
		}

		Assert(bms_equal(child_joinrel->relids, child_joinrelids));

		populate_joinrel_with_paths(root, child_rel1, child_rel2,
									child_joinrel, child_sjinfo,
									child_restrictlist);
	}
}