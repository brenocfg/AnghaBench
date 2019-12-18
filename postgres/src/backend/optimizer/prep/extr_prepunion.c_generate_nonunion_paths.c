#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;

/* Type definitions */
struct TYPE_49__ {double rows; } ;
struct TYPE_48__ {double tuple_fraction; } ;
struct TYPE_47__ {double rows; int /*<<< orphan*/  reltarget; int /*<<< orphan*/  relids; TYPE_4__* cheapest_total_path; } ;
struct TYPE_46__ {int op; int /*<<< orphan*/  colTypes; scalar_t__ all; int /*<<< orphan*/  colCollations; int /*<<< orphan*/  rarg; int /*<<< orphan*/  larg; } ;
typedef  TYPE_1__ SetOperationStmt ;
typedef  int /*<<< orphan*/  SetOpCmd ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ PlannerInfo ;
typedef  TYPE_4__ Path ;
typedef  TYPE_4__ List ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 double Min (double,double) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  SETOPCMD_EXCEPT ; 
 int /*<<< orphan*/  SETOPCMD_EXCEPT_ALL ; 
 int /*<<< orphan*/  SETOPCMD_INTERSECT ; 
 int /*<<< orphan*/  SETOPCMD_INTERSECT_ALL ; 
#define  SETOP_EXCEPT 129 
 int /*<<< orphan*/  SETOP_HASHED ; 
#define  SETOP_INTERSECT 128 
 int /*<<< orphan*/  SETOP_SORTED ; 
 int /*<<< orphan*/  UPPERREL_SETOP ; 
 int /*<<< orphan*/  add_path (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int choose_hashed_setop (TYPE_3__*,TYPE_4__*,TYPE_4__*,double,double,char*) ; 
 scalar_t__ create_append_path (TYPE_3__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  create_pathtarget (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ create_setop_path (TYPE_3__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int,double,double) ; 
 scalar_t__ create_sort_path (TYPE_3__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* fetch_upper_rel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* generate_append_tlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* generate_setop_grouplist (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 
 TYPE_4__* list_make2 (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  make_pathkeys_for_sortclauses (TYPE_3__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_2__* recurse_set_operations (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_4__*,TYPE_4__**,double*) ; 

__attribute__((used)) static RelOptInfo *
generate_nonunion_paths(SetOperationStmt *op, PlannerInfo *root,
						List *refnames_tlist,
						List **pTargetList)
{
	RelOptInfo *result_rel;
	RelOptInfo *lrel,
			   *rrel;
	double		save_fraction = root->tuple_fraction;
	Path	   *lpath,
			   *rpath,
			   *path;
	List	   *lpath_tlist,
			   *rpath_tlist,
			   *tlist_list,
			   *tlist,
			   *groupList,
			   *pathlist;
	double		dLeftGroups,
				dRightGroups,
				dNumGroups,
				dNumOutputRows;
	bool		use_hash;
	SetOpCmd	cmd;
	int			firstFlag;

	/*
	 * Tell children to fetch all tuples.
	 */
	root->tuple_fraction = 0.0;

	/* Recurse on children, ensuring their outputs are marked */
	lrel = recurse_set_operations(op->larg, root,
								  op->colTypes, op->colCollations,
								  false, 0,
								  refnames_tlist,
								  &lpath_tlist,
								  &dLeftGroups);
	lpath = lrel->cheapest_total_path;
	rrel = recurse_set_operations(op->rarg, root,
								  op->colTypes, op->colCollations,
								  false, 1,
								  refnames_tlist,
								  &rpath_tlist,
								  &dRightGroups);
	rpath = rrel->cheapest_total_path;

	/* Undo effects of forcing tuple_fraction to 0 */
	root->tuple_fraction = save_fraction;

	/*
	 * For EXCEPT, we must put the left input first.  For INTERSECT, either
	 * order should give the same results, and we prefer to put the smaller
	 * input first in order to minimize the size of the hash table in the
	 * hashing case.  "Smaller" means the one with the fewer groups.
	 */
	if (op->op == SETOP_EXCEPT || dLeftGroups <= dRightGroups)
	{
		pathlist = list_make2(lpath, rpath);
		tlist_list = list_make2(lpath_tlist, rpath_tlist);
		firstFlag = 0;
	}
	else
	{
		pathlist = list_make2(rpath, lpath);
		tlist_list = list_make2(rpath_tlist, lpath_tlist);
		firstFlag = 1;
	}

	/*
	 * Generate tlist for Append plan node.
	 *
	 * The tlist for an Append plan isn't important as far as the Append is
	 * concerned, but we must make it look real anyway for the benefit of the
	 * next plan level up.  In fact, it has to be real enough that the flag
	 * column is shown as a variable not a constant, else setrefs.c will get
	 * confused.
	 */
	tlist = generate_append_tlist(op->colTypes, op->colCollations, true,
								  tlist_list, refnames_tlist);

	*pTargetList = tlist;

	/* Build result relation. */
	result_rel = fetch_upper_rel(root, UPPERREL_SETOP,
								 bms_union(lrel->relids, rrel->relids));
	result_rel->reltarget = create_pathtarget(root, tlist);

	/*
	 * Append the child results together.
	 */
	path = (Path *) create_append_path(root, result_rel, pathlist, NIL,
									   NIL, NULL, 0, false, NIL, -1);

	/* Identify the grouping semantics */
	groupList = generate_setop_grouplist(op, tlist);

	/*
	 * Estimate number of distinct groups that we'll need hashtable entries
	 * for; this is the size of the left-hand input for EXCEPT, or the smaller
	 * input for INTERSECT.  Also estimate the number of eventual output rows.
	 * In non-ALL cases, we estimate each group produces one output row; in
	 * ALL cases use the relevant relation size.  These are worst-case
	 * estimates, of course, but we need to be conservative.
	 */
	if (op->op == SETOP_EXCEPT)
	{
		dNumGroups = dLeftGroups;
		dNumOutputRows = op->all ? lpath->rows : dNumGroups;
	}
	else
	{
		dNumGroups = Min(dLeftGroups, dRightGroups);
		dNumOutputRows = op->all ? Min(lpath->rows, rpath->rows) : dNumGroups;
	}

	/*
	 * Decide whether to hash or sort, and add a sort node if needed.
	 */
	use_hash = choose_hashed_setop(root, groupList, path,
								   dNumGroups, dNumOutputRows,
								   (op->op == SETOP_INTERSECT) ? "INTERSECT" : "EXCEPT");

	if (groupList && !use_hash)
		path = (Path *) create_sort_path(root,
										 result_rel,
										 path,
										 make_pathkeys_for_sortclauses(root,
																	   groupList,
																	   tlist),
										 -1.0);

	/*
	 * Finally, add a SetOp path node to generate the correct output.
	 */
	switch (op->op)
	{
		case SETOP_INTERSECT:
			cmd = op->all ? SETOPCMD_INTERSECT_ALL : SETOPCMD_INTERSECT;
			break;
		case SETOP_EXCEPT:
			cmd = op->all ? SETOPCMD_EXCEPT_ALL : SETOPCMD_EXCEPT;
			break;
		default:
			elog(ERROR, "unrecognized set op: %d", (int) op->op);
			cmd = SETOPCMD_INTERSECT;	/* keep compiler quiet */
			break;
	}
	path = (Path *) create_setop_path(root,
									  result_rel,
									  path,
									  cmd,
									  use_hash ? SETOP_HASHED : SETOP_SORTED,
									  groupList,
									  list_length(op->colTypes) + 1,
									  use_hash ? firstFlag : -1,
									  dNumGroups,
									  dNumOutputRows);

	result_rel->rows = path->rows;
	add_path(result_rel, path);
	return result_rel;
}