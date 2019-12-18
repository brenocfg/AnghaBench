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
struct TYPE_3__ {int simple_rel_array_size; int /*<<< orphan*/ ** append_rel_array; int /*<<< orphan*/ ** simple_rte_array; int /*<<< orphan*/ ** simple_rel_array; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ PlannerInfo ;
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc0 (int) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ **,int) ; 

void
expand_planner_arrays(PlannerInfo *root, int add_size)
{
	int			new_size;

	Assert(add_size > 0);

	new_size = root->simple_rel_array_size + add_size;

	root->simple_rel_array = (RelOptInfo **)
		repalloc(root->simple_rel_array,
				 sizeof(RelOptInfo *) * new_size);
	MemSet(root->simple_rel_array + root->simple_rel_array_size,
		   0, sizeof(RelOptInfo *) * add_size);

	root->simple_rte_array = (RangeTblEntry **)
		repalloc(root->simple_rte_array,
				 sizeof(RangeTblEntry *) * new_size);
	MemSet(root->simple_rte_array + root->simple_rel_array_size,
		   0, sizeof(RangeTblEntry *) * add_size);

	if (root->append_rel_array)
	{
		root->append_rel_array = (AppendRelInfo **)
			repalloc(root->append_rel_array,
					 sizeof(AppendRelInfo *) * new_size);
		MemSet(root->append_rel_array + root->simple_rel_array_size,
			   0, sizeof(AppendRelInfo *) * add_size);
	}
	else
	{
		root->append_rel_array = (AppendRelInfo **)
			palloc0(sizeof(AppendRelInfo *) * new_size);
	}

	root->simple_rel_array_size = new_size;
}