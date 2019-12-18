#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  orderClause; int /*<<< orphan*/  partitionClause; } ;
typedef  TYPE_1__ WindowClause ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  grouping_is_sortable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_concat_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_pathkeys_for_sortclauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
make_pathkeys_for_window(PlannerInfo *root, WindowClause *wc,
						 List *tlist)
{
	List	   *window_pathkeys;
	List	   *window_sortclauses;

	/* Throw error if can't sort */
	if (!grouping_is_sortable(wc->partitionClause))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("could not implement window PARTITION BY"),
				 errdetail("Window partitioning columns must be of sortable datatypes.")));
	if (!grouping_is_sortable(wc->orderClause))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("could not implement window ORDER BY"),
				 errdetail("Window ordering columns must be of sortable datatypes.")));

	/* Okay, make the combined pathkeys */
	window_sortclauses = list_concat_copy(wc->partitionClause, wc->orderClause);
	window_pathkeys = make_pathkeys_for_sortclauses(root,
													window_sortclauses,
													tlist);
	list_free(window_sortclauses);
	return window_pathkeys;
}