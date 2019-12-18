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
typedef  int /*<<< orphan*/  grouping_sets_data ;
typedef  int /*<<< orphan*/  child_extra ;
struct TYPE_25__ {int /*<<< orphan*/ * havingQual; int /*<<< orphan*/  target_parallel_safe; scalar_t__ patype; int /*<<< orphan*/ * targetList; } ;
struct TYPE_24__ {int /*<<< orphan*/ * exprs; } ;
struct TYPE_23__ {int nparts; scalar_t__ pathlist; int /*<<< orphan*/  relids; struct TYPE_23__** part_rels; TYPE_2__* reltarget; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ PathTarget ;
typedef  scalar_t__ PartitionwiseAggregateType ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ GroupPathExtraData ;
typedef  int /*<<< orphan*/  AppendRelInfo ;
typedef  int /*<<< orphan*/  AggClauseCosts ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_FULL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_NONE ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_PARTIAL ; 
 int /*<<< orphan*/  add_paths_to_append_rel (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ adjust_appendrel_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 TYPE_2__* copy_pathtarget (TYPE_2__*) ; 
 int /*<<< orphan*/  create_ordinary_grouping_paths (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__**) ; 
 int /*<<< orphan*/ ** find_appinfos_by_relids (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* make_grouping_rel (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_cheapest (TYPE_1__*) ; 

__attribute__((used)) static void
create_partitionwise_grouping_paths(PlannerInfo *root,
									RelOptInfo *input_rel,
									RelOptInfo *grouped_rel,
									RelOptInfo *partially_grouped_rel,
									const AggClauseCosts *agg_costs,
									grouping_sets_data *gd,
									PartitionwiseAggregateType patype,
									GroupPathExtraData *extra)
{
	int			nparts = input_rel->nparts;
	int			cnt_parts;
	List	   *grouped_live_children = NIL;
	List	   *partially_grouped_live_children = NIL;
	PathTarget *target = grouped_rel->reltarget;
	bool		partial_grouping_valid = true;

	Assert(patype != PARTITIONWISE_AGGREGATE_NONE);
	Assert(patype != PARTITIONWISE_AGGREGATE_PARTIAL ||
		   partially_grouped_rel != NULL);

	/* Add paths for partitionwise aggregation/grouping. */
	for (cnt_parts = 0; cnt_parts < nparts; cnt_parts++)
	{
		RelOptInfo *child_input_rel = input_rel->part_rels[cnt_parts];
		PathTarget *child_target = copy_pathtarget(target);
		AppendRelInfo **appinfos;
		int			nappinfos;
		GroupPathExtraData child_extra;
		RelOptInfo *child_grouped_rel;
		RelOptInfo *child_partially_grouped_rel;

		/* Pruned or dummy children can be ignored. */
		if (child_input_rel == NULL || IS_DUMMY_REL(child_input_rel))
			continue;

		/*
		 * Copy the given "extra" structure as is and then override the
		 * members specific to this child.
		 */
		memcpy(&child_extra, extra, sizeof(child_extra));

		appinfos = find_appinfos_by_relids(root, child_input_rel->relids,
										   &nappinfos);

		child_target->exprs = (List *)
			adjust_appendrel_attrs(root,
								   (Node *) target->exprs,
								   nappinfos, appinfos);

		/* Translate havingQual and targetList. */
		child_extra.havingQual = (Node *)
			adjust_appendrel_attrs(root,
								   extra->havingQual,
								   nappinfos, appinfos);
		child_extra.targetList = (List *)
			adjust_appendrel_attrs(root,
								   (Node *) extra->targetList,
								   nappinfos, appinfos);

		/*
		 * extra->patype was the value computed for our parent rel; patype is
		 * the value for this relation.  For the child, our value is its
		 * parent rel's value.
		 */
		child_extra.patype = patype;

		/*
		 * Create grouping relation to hold fully aggregated grouping and/or
		 * aggregation paths for the child.
		 */
		child_grouped_rel = make_grouping_rel(root, child_input_rel,
											  child_target,
											  extra->target_parallel_safe,
											  child_extra.havingQual);

		/* Create grouping paths for this child relation. */
		create_ordinary_grouping_paths(root, child_input_rel,
									   child_grouped_rel,
									   agg_costs, gd, &child_extra,
									   &child_partially_grouped_rel);

		if (child_partially_grouped_rel)
		{
			partially_grouped_live_children =
				lappend(partially_grouped_live_children,
						child_partially_grouped_rel);
		}
		else
			partial_grouping_valid = false;

		if (patype == PARTITIONWISE_AGGREGATE_FULL)
		{
			set_cheapest(child_grouped_rel);
			grouped_live_children = lappend(grouped_live_children,
											child_grouped_rel);
		}

		pfree(appinfos);
	}

	/*
	 * Try to create append paths for partially grouped children. For full
	 * partitionwise aggregation, we might have paths in the partial_pathlist
	 * if parallel aggregation is possible.  For partial partitionwise
	 * aggregation, we may have paths in both pathlist and partial_pathlist.
	 *
	 * NB: We must have a partially grouped path for every child in order to
	 * generate a partially grouped path for this relation.
	 */
	if (partially_grouped_rel && partial_grouping_valid)
	{
		Assert(partially_grouped_live_children != NIL);

		add_paths_to_append_rel(root, partially_grouped_rel,
								partially_grouped_live_children);

		/*
		 * We need call set_cheapest, since the finalization step will use the
		 * cheapest path from the rel.
		 */
		if (partially_grouped_rel->pathlist)
			set_cheapest(partially_grouped_rel);
	}

	/* If possible, create append paths for fully grouped children. */
	if (patype == PARTITIONWISE_AGGREGATE_FULL)
	{
		Assert(grouped_live_children != NIL);

		add_paths_to_append_rel(root, grouped_rel, grouped_live_children);
	}
}