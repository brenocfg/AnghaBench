#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pathtype; } ;
struct TYPE_6__ {int /*<<< orphan*/  joinrestrictinfo; TYPE_1__ path; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  NestPath ;
typedef  int /*<<< orphan*/  MergePath ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ JoinPath ;
typedef  int /*<<< orphan*/  HashPath ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ NIL ; 
#define  T_HashJoin 130 
#define  T_MergeJoin 129 
#define  T_NestLoop 128 
 int /*<<< orphan*/ * create_gating_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_hashjoin_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_mergejoin_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_nestloop_plan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_actual_clauses (scalar_t__) ; 
 int /*<<< orphan*/ * get_gating_quals (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_loc_restrictinfo (TYPE_2__*) ; 
 int /*<<< orphan*/  get_qpqual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_qpqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Plan *
create_join_plan(PlannerInfo *root, JoinPath *best_path)
{
	Plan	   *plan;
	List	   *gating_clauses;

	switch (best_path->path.pathtype)
	{
		case T_MergeJoin:
			plan = (Plan *) create_mergejoin_plan(root,
												  (MergePath *) best_path);
			break;
		case T_HashJoin:
			plan = (Plan *) create_hashjoin_plan(root,
												 (HashPath *) best_path);
			break;
		case T_NestLoop:
			plan = (Plan *) create_nestloop_plan(root,
												 (NestPath *) best_path);
			break;
		default:
			elog(ERROR, "unrecognized node type: %d",
				 (int) best_path->path.pathtype);
			plan = NULL;		/* keep compiler quiet */
			break;
	}

	/*
	 * If there are any pseudoconstant clauses attached to this node, insert a
	 * gating Result node that evaluates the pseudoconstants as one-time
	 * quals.
	 */
	gating_clauses = get_gating_quals(root, best_path->joinrestrictinfo);
	if (gating_clauses)
		plan = create_gating_plan(root, (Path *) best_path, plan,
								  gating_clauses);

#ifdef NOT_USED

	/*
	 * * Expensive function pullups may have pulled local predicates * into
	 * this path node.  Put them in the qpqual of the plan node. * JMH,
	 * 6/15/92
	 */
	if (get_loc_restrictinfo(best_path) != NIL)
		set_qpqual((Plan) plan,
				   list_concat(get_qpqual((Plan) plan),
							   get_actual_clauses(get_loc_restrictinfo(best_path))));
#endif

	return plan;
}