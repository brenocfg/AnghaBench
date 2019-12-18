#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grouping_sets_data ;
struct TYPE_51__ {scalar_t__ patype; int flags; int /*<<< orphan*/  targetList; } ;
struct TYPE_50__ {int /*<<< orphan*/  rows; } ;
struct TYPE_49__ {TYPE_1__* parse; } ;
struct TYPE_48__ {scalar_t__ pathlist; TYPE_2__* fdwroutine; scalar_t__ partial_pathlist; TYPE_5__* cheapest_total_path; } ;
struct TYPE_47__ {int /*<<< orphan*/  (* GetForeignUpperPaths ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_6__*) ;} ;
struct TYPE_46__ {int /*<<< orphan*/  groupClause; } ;
typedef  TYPE_3__ RelOptInfo ;
typedef  TYPE_4__ PlannerInfo ;
typedef  TYPE_5__ Path ;
typedef  scalar_t__ PartitionwiseAggregateType ;
typedef  TYPE_6__ GroupPathExtraData ;
typedef  int /*<<< orphan*/  AggClauseCosts ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (TYPE_3__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int GROUPING_CAN_PARTIAL_AGG ; 
 scalar_t__ IS_PARTITIONED_REL (TYPE_3__*) ; 
 scalar_t__ NIL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_FULL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_NONE ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_PARTIAL ; 
 int /*<<< orphan*/  UPPERREL_GROUP_AGG ; 
 int /*<<< orphan*/  add_paths_to_grouping_rel (TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,double,TYPE_6__*) ; 
 TYPE_3__* create_partial_grouping_paths (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  create_partitionwise_grouping_paths (TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__,TYPE_6__*) ; 
 int /*<<< orphan*/  create_upper_paths_hook (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  gather_grouping_paths (TYPE_4__*,TYPE_3__*) ; 
 double get_number_of_groups (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ group_by_has_partkey (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cheapest (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static void
create_ordinary_grouping_paths(PlannerInfo *root, RelOptInfo *input_rel,
							   RelOptInfo *grouped_rel,
							   const AggClauseCosts *agg_costs,
							   grouping_sets_data *gd,
							   GroupPathExtraData *extra,
							   RelOptInfo **partially_grouped_rel_p)
{
	Path	   *cheapest_path = input_rel->cheapest_total_path;
	RelOptInfo *partially_grouped_rel = NULL;
	double		dNumGroups;
	PartitionwiseAggregateType patype = PARTITIONWISE_AGGREGATE_NONE;

	/*
	 * If this is the topmost grouping relation or if the parent relation is
	 * doing some form of partitionwise aggregation, then we may be able to do
	 * it at this level also.  However, if the input relation is not
	 * partitioned, partitionwise aggregate is impossible.
	 */
	if (extra->patype != PARTITIONWISE_AGGREGATE_NONE &&
		IS_PARTITIONED_REL(input_rel))
	{
		/*
		 * If this is the topmost relation or if the parent relation is doing
		 * full partitionwise aggregation, then we can do full partitionwise
		 * aggregation provided that the GROUP BY clause contains all of the
		 * partitioning columns at this level.  Otherwise, we can do at most
		 * partial partitionwise aggregation.  But if partial aggregation is
		 * not supported in general then we can't use it for partitionwise
		 * aggregation either.
		 */
		if (extra->patype == PARTITIONWISE_AGGREGATE_FULL &&
			group_by_has_partkey(input_rel, extra->targetList,
								 root->parse->groupClause))
			patype = PARTITIONWISE_AGGREGATE_FULL;
		else if ((extra->flags & GROUPING_CAN_PARTIAL_AGG) != 0)
			patype = PARTITIONWISE_AGGREGATE_PARTIAL;
		else
			patype = PARTITIONWISE_AGGREGATE_NONE;
	}

	/*
	 * Before generating paths for grouped_rel, we first generate any possible
	 * partially grouped paths; that way, later code can easily consider both
	 * parallel and non-parallel approaches to grouping.
	 */
	if ((extra->flags & GROUPING_CAN_PARTIAL_AGG) != 0)
	{
		bool		force_rel_creation;

		/*
		 * If we're doing partitionwise aggregation at this level, force
		 * creation of a partially_grouped_rel so we can add partitionwise
		 * paths to it.
		 */
		force_rel_creation = (patype == PARTITIONWISE_AGGREGATE_PARTIAL);

		partially_grouped_rel =
			create_partial_grouping_paths(root,
										  grouped_rel,
										  input_rel,
										  gd,
										  extra,
										  force_rel_creation);
	}

	/* Set out parameter. */
	*partially_grouped_rel_p = partially_grouped_rel;

	/* Apply partitionwise aggregation technique, if possible. */
	if (patype != PARTITIONWISE_AGGREGATE_NONE)
		create_partitionwise_grouping_paths(root, input_rel, grouped_rel,
											partially_grouped_rel, agg_costs,
											gd, patype, extra);

	/* If we are doing partial aggregation only, return. */
	if (extra->patype == PARTITIONWISE_AGGREGATE_PARTIAL)
	{
		Assert(partially_grouped_rel);

		if (partially_grouped_rel->pathlist)
			set_cheapest(partially_grouped_rel);

		return;
	}

	/* Gather any partially grouped partial paths. */
	if (partially_grouped_rel && partially_grouped_rel->partial_pathlist)
	{
		gather_grouping_paths(root, partially_grouped_rel);
		set_cheapest(partially_grouped_rel);
	}

	/*
	 * Estimate number of groups.
	 */
	dNumGroups = get_number_of_groups(root,
									  cheapest_path->rows,
									  gd,
									  extra->targetList);

	/* Build final grouping paths */
	add_paths_to_grouping_rel(root, input_rel, grouped_rel,
							  partially_grouped_rel, agg_costs, gd,
							  dNumGroups, extra);

	/* Give a helpful error if we failed to find any implementation */
	if (grouped_rel->pathlist == NIL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("could not implement GROUP BY"),
				 errdetail("Some of the datatypes only support hashing, while others only support sorting.")));

	/*
	 * If there is an FDW that's responsible for all baserels of the query,
	 * let it consider adding ForeignPaths.
	 */
	if (grouped_rel->fdwroutine &&
		grouped_rel->fdwroutine->GetForeignUpperPaths)
		grouped_rel->fdwroutine->GetForeignUpperPaths(root, UPPERREL_GROUP_AGG,
													  input_rel, grouped_rel,
													  extra);

	/* Let extensions possibly add some more paths */
	if (create_upper_paths_hook)
		(*create_upper_paths_hook) (root, UPPERREL_GROUP_AGG,
									input_rel, grouped_rel,
									extra);
}