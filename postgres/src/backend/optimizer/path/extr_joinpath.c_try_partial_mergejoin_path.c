#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  total_cost; } ;
struct TYPE_25__ {int /*<<< orphan*/  restrictlist; } ;
struct TYPE_24__ {int /*<<< orphan*/  pathkeys; TYPE_1__* param_info; } ;
struct TYPE_23__ {int /*<<< orphan*/  lateral_relids; } ;
struct TYPE_22__ {int /*<<< orphan*/  ppi_req_outer; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ Path ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  TYPE_4__ JoinPathExtraData ;
typedef  TYPE_5__ JoinCostWorkspace ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  add_partial_path (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  add_partial_path_precheck (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ create_mergejoin_path (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initial_cost_mergejoin (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ pathkeys_contained_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
try_partial_mergejoin_path(PlannerInfo *root,
						   RelOptInfo *joinrel,
						   Path *outer_path,
						   Path *inner_path,
						   List *pathkeys,
						   List *mergeclauses,
						   List *outersortkeys,
						   List *innersortkeys,
						   JoinType jointype,
						   JoinPathExtraData *extra)
{
	JoinCostWorkspace workspace;

	/*
	 * See comments in try_partial_hashjoin_path().
	 */
	Assert(bms_is_empty(joinrel->lateral_relids));
	if (inner_path->param_info != NULL)
	{
		Relids		inner_paramrels = inner_path->param_info->ppi_req_outer;

		if (!bms_is_empty(inner_paramrels))
			return;
	}

	/*
	 * If the given paths are already well enough ordered, we can skip doing
	 * an explicit sort.
	 */
	if (outersortkeys &&
		pathkeys_contained_in(outersortkeys, outer_path->pathkeys))
		outersortkeys = NIL;
	if (innersortkeys &&
		pathkeys_contained_in(innersortkeys, inner_path->pathkeys))
		innersortkeys = NIL;

	/*
	 * See comments in try_partial_nestloop_path().
	 */
	initial_cost_mergejoin(root, &workspace, jointype, mergeclauses,
						   outer_path, inner_path,
						   outersortkeys, innersortkeys,
						   extra);

	if (!add_partial_path_precheck(joinrel, workspace.total_cost, pathkeys))
		return;

	/* Might be good enough to be worth trying, so let's try it. */
	add_partial_path(joinrel, (Path *)
					 create_mergejoin_path(root,
										   joinrel,
										   jointype,
										   &workspace,
										   extra,
										   outer_path,
										   inner_path,
										   extra->restrictlist,
										   pathkeys,
										   NULL,
										   mergeclauses,
										   outersortkeys,
										   innersortkeys));
}