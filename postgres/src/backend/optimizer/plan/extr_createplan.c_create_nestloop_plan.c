#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  plan; } ;
struct TYPE_26__ {TYPE_3__ join; } ;
struct TYPE_20__ {scalar_t__ param_info; TYPE_1__* parent; } ;
struct TYPE_25__ {TYPE_16__ path; int /*<<< orphan*/  inner_unique; int /*<<< orphan*/  jointype; TYPE_12__* outerjoinpath; TYPE_12__* innerjoinpath; int /*<<< orphan*/ * joinrestrictinfo; } ;
struct TYPE_24__ {int /*<<< orphan*/  curOuterRels; } ;
struct TYPE_22__ {int /*<<< orphan*/  relids; } ;
struct TYPE_21__ {int /*<<< orphan*/  relids; } ;
struct TYPE_19__ {TYPE_2__* parent; } ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_4__ PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_5__ NestPath ;
typedef  TYPE_6__ NestLoop ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ IS_OUTER_JOIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_path_tlist (TYPE_4__*,TYPE_16__*) ; 
 int /*<<< orphan*/  copy_generic_path_info (int /*<<< orphan*/ *,TYPE_16__*) ; 
 int /*<<< orphan*/ * create_plan_recurse (TYPE_4__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * extract_actual_clauses (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extract_actual_join_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * identify_current_nestloop_params (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* make_nestloop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * order_qual_clauses (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ replace_nestloop_params (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NestLoop *
create_nestloop_plan(PlannerInfo *root,
					 NestPath *best_path)
{
	NestLoop   *join_plan;
	Plan	   *outer_plan;
	Plan	   *inner_plan;
	List	   *tlist = build_path_tlist(root, &best_path->path);
	List	   *joinrestrictclauses = best_path->joinrestrictinfo;
	List	   *joinclauses;
	List	   *otherclauses;
	Relids		outerrelids;
	List	   *nestParams;
	Relids		saveOuterRels = root->curOuterRels;

	/* NestLoop can project, so no need to be picky about child tlists */
	outer_plan = create_plan_recurse(root, best_path->outerjoinpath, 0);

	/* For a nestloop, include outer relids in curOuterRels for inner side */
	root->curOuterRels = bms_union(root->curOuterRels,
								   best_path->outerjoinpath->parent->relids);

	inner_plan = create_plan_recurse(root, best_path->innerjoinpath, 0);

	/* Restore curOuterRels */
	bms_free(root->curOuterRels);
	root->curOuterRels = saveOuterRels;

	/* Sort join qual clauses into best execution order */
	joinrestrictclauses = order_qual_clauses(root, joinrestrictclauses);

	/* Get the join qual clauses (in plain expression form) */
	/* Any pseudoconstant clauses are ignored here */
	if (IS_OUTER_JOIN(best_path->jointype))
	{
		extract_actual_join_clauses(joinrestrictclauses,
									best_path->path.parent->relids,
									&joinclauses, &otherclauses);
	}
	else
	{
		/* We can treat all clauses alike for an inner join */
		joinclauses = extract_actual_clauses(joinrestrictclauses, false);
		otherclauses = NIL;
	}

	/* Replace any outer-relation variables with nestloop params */
	if (best_path->path.param_info)
	{
		joinclauses = (List *)
			replace_nestloop_params(root, (Node *) joinclauses);
		otherclauses = (List *)
			replace_nestloop_params(root, (Node *) otherclauses);
	}

	/*
	 * Identify any nestloop parameters that should be supplied by this join
	 * node, and remove them from root->curOuterParams.
	 */
	outerrelids = best_path->outerjoinpath->parent->relids;
	nestParams = identify_current_nestloop_params(root, outerrelids);

	join_plan = make_nestloop(tlist,
							  joinclauses,
							  otherclauses,
							  nestParams,
							  outer_plan,
							  inner_plan,
							  best_path->jointype,
							  best_path->inner_unique);

	copy_generic_path_info(&join_plan->join.plan, &best_path->path);

	return join_plan;
}