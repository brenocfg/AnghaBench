#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_8__ {int /*<<< orphan*/  restrictlist; int /*<<< orphan*/  param_source_rels; } ;
typedef  scalar_t__ Relids ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  TYPE_1__ JoinPathExtraData ;
typedef  TYPE_2__ JoinCostWorkspace ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  add_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ add_path_precheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bms_free (scalar_t__) ; 
 int /*<<< orphan*/  bms_overlap (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ calc_non_nestloop_required_outer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_hashjoin_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initial_cost_hashjoin (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
try_hashjoin_path(PlannerInfo *root,
				  RelOptInfo *joinrel,
				  Path *outer_path,
				  Path *inner_path,
				  List *hashclauses,
				  JoinType jointype,
				  JoinPathExtraData *extra)
{
	Relids		required_outer;
	JoinCostWorkspace workspace;

	/*
	 * Check to see if proposed path is still parameterized, and reject if the
	 * parameterization wouldn't be sensible.
	 */
	required_outer = calc_non_nestloop_required_outer(outer_path,
													  inner_path);
	if (required_outer &&
		!bms_overlap(required_outer, extra->param_source_rels))
	{
		/* Waste no memory when we reject a path here */
		bms_free(required_outer);
		return;
	}

	/*
	 * See comments in try_nestloop_path().  Also note that hashjoin paths
	 * never have any output pathkeys, per comments in create_hashjoin_path.
	 */
	initial_cost_hashjoin(root, &workspace, jointype, hashclauses,
						  outer_path, inner_path, extra, false);

	if (add_path_precheck(joinrel,
						  workspace.startup_cost, workspace.total_cost,
						  NIL, required_outer))
	{
		add_path(joinrel, (Path *)
				 create_hashjoin_path(root,
									  joinrel,
									  jointype,
									  &workspace,
									  extra,
									  outer_path,
									  inner_path,
									  false,	/* parallel_hash */
									  extra->restrictlist,
									  required_outer,
									  hashclauses));
	}
	else
	{
		/* Waste no memory when we reject a path here */
		bms_free(required_outer);
	}
}