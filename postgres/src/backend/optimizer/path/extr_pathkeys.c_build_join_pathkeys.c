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
typedef  scalar_t__ JoinType ;

/* Variables and functions */
 scalar_t__ JOIN_FULL ; 
 scalar_t__ JOIN_RIGHT ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * truncate_useless_pathkeys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

List *
build_join_pathkeys(PlannerInfo *root,
					RelOptInfo *joinrel,
					JoinType jointype,
					List *outer_pathkeys)
{
	if (jointype == JOIN_FULL || jointype == JOIN_RIGHT)
		return NIL;

	/*
	 * This used to be quite a complex bit of code, but now that all pathkey
	 * sublists start out life canonicalized, we don't have to do a darn thing
	 * here!
	 *
	 * We do, however, need to truncate the pathkeys list, since it may
	 * contain pathkeys that were useful for forming this joinrel but are
	 * uninteresting to higher levels.
	 */
	return truncate_useless_pathkeys(root, joinrel, outer_pathkeys);
}