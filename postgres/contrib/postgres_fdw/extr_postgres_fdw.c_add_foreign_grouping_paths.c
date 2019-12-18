#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ patype; int /*<<< orphan*/  havingQual; } ;
struct TYPE_24__ {double rows; int width; void* total_cost; void* startup_cost; int /*<<< orphan*/  local_conds; int /*<<< orphan*/  local_conds_cost; int /*<<< orphan*/  local_conds_sel; int /*<<< orphan*/  user; int /*<<< orphan*/  server; int /*<<< orphan*/  table; TYPE_1__* outerrel; } ;
struct TYPE_23__ {int /*<<< orphan*/  hasHavingQual; TYPE_2__* parse; } ;
struct TYPE_22__ {int /*<<< orphan*/  hasAggs; int /*<<< orphan*/  groupingSets; int /*<<< orphan*/  groupClause; } ;
struct TYPE_21__ {int /*<<< orphan*/  reltarget; TYPE_4__* fdw_private; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerInfo ;
typedef  TYPE_4__ PgFdwRelationInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  TYPE_5__ GroupPathExtraData ;
typedef  int /*<<< orphan*/  ForeignPath ;
typedef  void* Cost ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JOIN_INNER ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_FULL ; 
 scalar_t__ PARTITIONWISE_AGGREGATE_NONE ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clauselist_selectivity (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cost_qual_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * create_foreign_upper_path (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,double,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estimate_path_cost_size (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*,int*,void**,void**) ; 
 int /*<<< orphan*/  foreign_grouping_ok (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_fdw_options (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_foreign_grouping_paths(PlannerInfo *root, RelOptInfo *input_rel,
						   RelOptInfo *grouped_rel,
						   GroupPathExtraData *extra)
{
	Query	   *parse = root->parse;
	PgFdwRelationInfo *ifpinfo = input_rel->fdw_private;
	PgFdwRelationInfo *fpinfo = grouped_rel->fdw_private;
	ForeignPath *grouppath;
	double		rows;
	int			width;
	Cost		startup_cost;
	Cost		total_cost;

	/* Nothing to be done, if there is no grouping or aggregation required. */
	if (!parse->groupClause && !parse->groupingSets && !parse->hasAggs &&
		!root->hasHavingQual)
		return;

	Assert(extra->patype == PARTITIONWISE_AGGREGATE_NONE ||
		   extra->patype == PARTITIONWISE_AGGREGATE_FULL);

	/* save the input_rel as outerrel in fpinfo */
	fpinfo->outerrel = input_rel;

	/*
	 * Copy foreign table, foreign server, user mapping, FDW options etc.
	 * details from the input relation's fpinfo.
	 */
	fpinfo->table = ifpinfo->table;
	fpinfo->server = ifpinfo->server;
	fpinfo->user = ifpinfo->user;
	merge_fdw_options(fpinfo, ifpinfo, NULL);

	/*
	 * Assess if it is safe to push down aggregation and grouping.
	 *
	 * Use HAVING qual from extra. In case of child partition, it will have
	 * translated Vars.
	 */
	if (!foreign_grouping_ok(root, grouped_rel, extra->havingQual))
		return;

	/*
	 * Compute the selectivity and cost of the local_conds, so we don't have
	 * to do it over again for each path.  (Currently we create just a single
	 * path here, but in future it would be possible that we build more paths
	 * such as pre-sorted paths as in postgresGetForeignPaths and
	 * postgresGetForeignJoinPaths.)  The best we can do for these conditions
	 * is to estimate selectivity on the basis of local statistics.
	 */
	fpinfo->local_conds_sel = clauselist_selectivity(root,
													 fpinfo->local_conds,
													 0,
													 JOIN_INNER,
													 NULL);

	cost_qual_eval(&fpinfo->local_conds_cost, fpinfo->local_conds, root);

	/* Estimate the cost of push down */
	estimate_path_cost_size(root, grouped_rel, NIL, NIL, NULL,
							&rows, &width, &startup_cost, &total_cost);

	/* Now update this information in the fpinfo */
	fpinfo->rows = rows;
	fpinfo->width = width;
	fpinfo->startup_cost = startup_cost;
	fpinfo->total_cost = total_cost;

	/* Create and add foreign path to the grouping relation. */
	grouppath = create_foreign_upper_path(root,
										  grouped_rel,
										  grouped_rel->reltarget,
										  rows,
										  startup_cost,
										  total_cost,
										  NIL,	/* no pathkeys */
										  NULL,
										  NIL); /* no fdw_private */

	/* Add generated path into grouped_rel by add_path(). */
	add_path(grouped_rel, (Path *) grouppath);
}