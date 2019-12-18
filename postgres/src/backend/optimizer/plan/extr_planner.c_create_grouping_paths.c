#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ rollups; scalar_t__ any_hashable; } ;
typedef  TYPE_1__ grouping_sets_data ;
struct TYPE_22__ {scalar_t__ numOrderedAggs; } ;
struct TYPE_21__ {int flags; int target_parallel_safe; int partial_costs_set; int /*<<< orphan*/  patype; int /*<<< orphan*/  targetList; int /*<<< orphan*/  havingQual; } ;
struct TYPE_20__ {TYPE_2__* parse; } ;
struct TYPE_19__ {scalar_t__ groupClause; int /*<<< orphan*/  groupingSets; int /*<<< orphan*/  targetList; int /*<<< orphan*/  havingQual; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  PathTarget ;
typedef  TYPE_4__ GroupPathExtraData ;
typedef  TYPE_5__ AggClauseCosts ;

/* Variables and functions */
 int GROUPING_CAN_PARTIAL_AGG ; 
 int GROUPING_CAN_USE_HASH ; 
 int GROUPING_CAN_USE_SORT ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  PARTITIONWISE_AGGREGATE_FULL ; 
 int /*<<< orphan*/  PARTITIONWISE_AGGREGATE_NONE ; 
 scalar_t__ can_partial_agg (TYPE_3__*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  create_degenerate_grouping_paths (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_ordinary_grouping_paths (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__ const*,TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ **) ; 
 scalar_t__ enable_partitionwise_aggregate ; 
 scalar_t__ grouping_is_hashable (scalar_t__) ; 
 scalar_t__ grouping_is_sortable (scalar_t__) ; 
 scalar_t__ is_degenerate_grouping (TYPE_3__*) ; 
 int /*<<< orphan*/ * make_grouping_rel (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cheapest (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RelOptInfo *
create_grouping_paths(PlannerInfo *root,
					  RelOptInfo *input_rel,
					  PathTarget *target,
					  bool target_parallel_safe,
					  const AggClauseCosts *agg_costs,
					  grouping_sets_data *gd)
{
	Query	   *parse = root->parse;
	RelOptInfo *grouped_rel;
	RelOptInfo *partially_grouped_rel;

	/*
	 * Create grouping relation to hold fully aggregated grouping and/or
	 * aggregation paths.
	 */
	grouped_rel = make_grouping_rel(root, input_rel, target,
									target_parallel_safe, parse->havingQual);

	/*
	 * Create either paths for a degenerate grouping or paths for ordinary
	 * grouping, as appropriate.
	 */
	if (is_degenerate_grouping(root))
		create_degenerate_grouping_paths(root, input_rel, grouped_rel);
	else
	{
		int			flags = 0;
		GroupPathExtraData extra;

		/*
		 * Determine whether it's possible to perform sort-based
		 * implementations of grouping.  (Note that if groupClause is empty,
		 * grouping_is_sortable() is trivially true, and all the
		 * pathkeys_contained_in() tests will succeed too, so that we'll
		 * consider every surviving input path.)
		 *
		 * If we have grouping sets, we might be able to sort some but not all
		 * of them; in this case, we need can_sort to be true as long as we
		 * must consider any sorted-input plan.
		 */
		if ((gd && gd->rollups != NIL)
			|| grouping_is_sortable(parse->groupClause))
			flags |= GROUPING_CAN_USE_SORT;

		/*
		 * Determine whether we should consider hash-based implementations of
		 * grouping.
		 *
		 * Hashed aggregation only applies if we're grouping. If we have
		 * grouping sets, some groups might be hashable but others not; in
		 * this case we set can_hash true as long as there is nothing globally
		 * preventing us from hashing (and we should therefore consider plans
		 * with hashes).
		 *
		 * Executor doesn't support hashed aggregation with DISTINCT or ORDER
		 * BY aggregates.  (Doing so would imply storing *all* the input
		 * values in the hash table, and/or running many sorts in parallel,
		 * either of which seems like a certain loser.)  We similarly don't
		 * support ordered-set aggregates in hashed aggregation, but that case
		 * is also included in the numOrderedAggs count.
		 *
		 * Note: grouping_is_hashable() is much more expensive to check than
		 * the other gating conditions, so we want to do it last.
		 */
		if ((parse->groupClause != NIL &&
			 agg_costs->numOrderedAggs == 0 &&
			 (gd ? gd->any_hashable : grouping_is_hashable(parse->groupClause))))
			flags |= GROUPING_CAN_USE_HASH;

		/*
		 * Determine whether partial aggregation is possible.
		 */
		if (can_partial_agg(root, agg_costs))
			flags |= GROUPING_CAN_PARTIAL_AGG;

		extra.flags = flags;
		extra.target_parallel_safe = target_parallel_safe;
		extra.havingQual = parse->havingQual;
		extra.targetList = parse->targetList;
		extra.partial_costs_set = false;

		/*
		 * Determine whether partitionwise aggregation is in theory possible.
		 * It can be disabled by the user, and for now, we don't try to
		 * support grouping sets.  create_ordinary_grouping_paths() will check
		 * additional conditions, such as whether input_rel is partitioned.
		 */
		if (enable_partitionwise_aggregate && !parse->groupingSets)
			extra.patype = PARTITIONWISE_AGGREGATE_FULL;
		else
			extra.patype = PARTITIONWISE_AGGREGATE_NONE;

		create_ordinary_grouping_paths(root, input_rel, grouped_rel,
									   agg_costs, gd, &extra,
									   &partially_grouped_rel);
	}

	set_cheapest(grouped_rel);
	return grouped_rel;
}