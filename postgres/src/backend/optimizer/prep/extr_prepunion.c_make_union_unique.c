#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double rows; int /*<<< orphan*/  pathkeys; } ;
typedef  int /*<<< orphan*/  SetOperationStmt ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AGGSPLIT_SIMPLE ; 
 int /*<<< orphan*/  AGG_HASHED ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  UPPERREL_SETOP ; 
 scalar_t__ choose_hashed_setop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,double,double,char*) ; 
 scalar_t__ create_agg_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  create_pathtarget (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ create_sort_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,double) ; 
 scalar_t__ create_upper_unique_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * fetch_upper_rel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * generate_setop_grouplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_pathkeys_for_sortclauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Path *
make_union_unique(SetOperationStmt *op, Path *path, List *tlist,
				  PlannerInfo *root)
{
	RelOptInfo *result_rel = fetch_upper_rel(root, UPPERREL_SETOP, NULL);
	List	   *groupList;
	double		dNumGroups;

	/* Identify the grouping semantics */
	groupList = generate_setop_grouplist(op, tlist);

	/*
	 * XXX for the moment, take the number of distinct groups as equal to the
	 * total input size, ie, the worst case.  This is too conservative, but we
	 * don't want to risk having the hashtable overrun memory; also, it's not
	 * clear how to get a decent estimate of the true size.  One should note
	 * as well the propensity of novices to write UNION rather than UNION ALL
	 * even when they don't expect any duplicates...
	 */
	dNumGroups = path->rows;

	/* Decide whether to hash or sort */
	if (choose_hashed_setop(root, groupList, path,
							dNumGroups, dNumGroups,
							"UNION"))
	{
		/* Hashed aggregate plan --- no sort needed */
		path = (Path *) create_agg_path(root,
										result_rel,
										path,
										create_pathtarget(root, tlist),
										AGG_HASHED,
										AGGSPLIT_SIMPLE,
										groupList,
										NIL,
										NULL,
										dNumGroups);
	}
	else
	{
		/* Sort and Unique */
		if (groupList)
			path = (Path *)
				create_sort_path(root,
								 result_rel,
								 path,
								 make_pathkeys_for_sortclauses(root,
															   groupList,
															   tlist),
								 -1.0);
		path = (Path *) create_upper_unique_path(root,
												 result_rel,
												 path,
												 list_length(path->pathkeys),
												 dNumGroups);
	}

	return path;
}