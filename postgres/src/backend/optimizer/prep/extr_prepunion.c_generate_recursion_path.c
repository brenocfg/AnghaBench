#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int rows; } ;
struct TYPE_24__ {int /*<<< orphan*/  wt_param_id; TYPE_4__* non_recursive_path; } ;
struct TYPE_23__ {int /*<<< orphan*/  reltarget; int /*<<< orphan*/  relids; TYPE_4__* cheapest_total_path; } ;
struct TYPE_22__ {scalar_t__ op; scalar_t__ all; int /*<<< orphan*/  colCollations; int /*<<< orphan*/  colTypes; int /*<<< orphan*/  rarg; int /*<<< orphan*/  larg; } ;
typedef  TYPE_1__ SetOperationStmt ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ PlannerInfo ;
typedef  TYPE_4__ Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ SETOP_UNION ; 
 int /*<<< orphan*/  UPPERREL_SETOP ; 
 int /*<<< orphan*/  add_path (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_pathtarget (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ create_recursiveunion_path (TYPE_3__*,TYPE_2__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_2__* fetch_upper_rel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * generate_append_tlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * generate_setop_grouplist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grouping_is_hashable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  postprocess_setop_rel (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* recurse_set_operations (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RelOptInfo *
generate_recursion_path(SetOperationStmt *setOp, PlannerInfo *root,
						List *refnames_tlist,
						List **pTargetList)
{
	RelOptInfo *result_rel;
	Path	   *path;
	RelOptInfo *lrel,
			   *rrel;
	Path	   *lpath;
	Path	   *rpath;
	List	   *lpath_tlist;
	List	   *rpath_tlist;
	List	   *tlist;
	List	   *groupList;
	double		dNumGroups;

	/* Parser should have rejected other cases */
	if (setOp->op != SETOP_UNION)
		elog(ERROR, "only UNION queries can be recursive");
	/* Worktable ID should be assigned */
	Assert(root->wt_param_id >= 0);

	/*
	 * Unlike a regular UNION node, process the left and right inputs
	 * separately without any intention of combining them into one Append.
	 */
	lrel = recurse_set_operations(setOp->larg, root,
								  setOp->colTypes, setOp->colCollations,
								  false, -1,
								  refnames_tlist,
								  &lpath_tlist,
								  NULL);
	lpath = lrel->cheapest_total_path;
	/* The right path will want to look at the left one ... */
	root->non_recursive_path = lpath;
	rrel = recurse_set_operations(setOp->rarg, root,
								  setOp->colTypes, setOp->colCollations,
								  false, -1,
								  refnames_tlist,
								  &rpath_tlist,
								  NULL);
	rpath = rrel->cheapest_total_path;
	root->non_recursive_path = NULL;

	/*
	 * Generate tlist for RecursiveUnion path node --- same as in Append cases
	 */
	tlist = generate_append_tlist(setOp->colTypes, setOp->colCollations, false,
								  list_make2(lpath_tlist, rpath_tlist),
								  refnames_tlist);

	*pTargetList = tlist;

	/* Build result relation. */
	result_rel = fetch_upper_rel(root, UPPERREL_SETOP,
								 bms_union(lrel->relids, rrel->relids));
	result_rel->reltarget = create_pathtarget(root, tlist);

	/*
	 * If UNION, identify the grouping operators
	 */
	if (setOp->all)
	{
		groupList = NIL;
		dNumGroups = 0;
	}
	else
	{
		/* Identify the grouping semantics */
		groupList = generate_setop_grouplist(setOp, tlist);

		/* We only support hashing here */
		if (!grouping_is_hashable(groupList))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("could not implement recursive UNION"),
					 errdetail("All column datatypes must be hashable.")));

		/*
		 * For the moment, take the number of distinct groups as equal to the
		 * total input size, ie, the worst case.
		 */
		dNumGroups = lpath->rows + rpath->rows * 10;
	}

	/*
	 * And make the path node.
	 */
	path = (Path *) create_recursiveunion_path(root,
											   result_rel,
											   lpath,
											   rpath,
											   result_rel->reltarget,
											   groupList,
											   root->wt_param_id,
											   dNumGroups);

	add_path(result_rel, path);
	postprocess_setop_rel(root, result_rel);
	return result_rel;
}