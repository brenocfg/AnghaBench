#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,int) ; 
 int pathkeys_useful_for_merging (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pathkeys_useful_for_ordering (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
truncate_useless_pathkeys(PlannerInfo *root,
						  RelOptInfo *rel,
						  List *pathkeys)
{
	int			nuseful;
	int			nuseful2;

	nuseful = pathkeys_useful_for_merging(root, rel, pathkeys);
	nuseful2 = pathkeys_useful_for_ordering(root, pathkeys);
	if (nuseful2 > nuseful)
		nuseful = nuseful2;

	/*
	 * Note: not safe to modify input list destructively, but we can avoid
	 * copying the list if we're not actually going to change it
	 */
	if (nuseful == 0)
		return NIL;
	else if (nuseful == list_length(pathkeys))
		return pathkeys;
	else
		return list_truncate(list_copy(pathkeys), nuseful);
}