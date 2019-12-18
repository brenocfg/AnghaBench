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
struct TYPE_3__ {int /*<<< orphan*/  joininfo; } ;
typedef  int /*<<< orphan*/  RestrictInfo ;
typedef  int /*<<< orphan*/  Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* find_base_rel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_delete_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_member_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
remove_join_clause_from_rels(PlannerInfo *root,
							 RestrictInfo *restrictinfo,
							 Relids join_relids)
{
	int			cur_relid;

	cur_relid = -1;
	while ((cur_relid = bms_next_member(join_relids, cur_relid)) >= 0)
	{
		RelOptInfo *rel = find_base_rel(root, cur_relid);

		/*
		 * Remove the restrictinfo from the list.  Pointer comparison is
		 * sufficient.
		 */
		Assert(list_member_ptr(rel->joininfo, restrictinfo));
		rel->joininfo = list_delete_ptr(rel->joininfo, restrictinfo);
	}
}