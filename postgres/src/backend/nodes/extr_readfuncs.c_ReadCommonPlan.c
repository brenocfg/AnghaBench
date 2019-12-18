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
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  READ_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_FLOAT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_TEMP_LOCALS () ; 
 int /*<<< orphan*/  allParam ; 
 int /*<<< orphan*/  extParam ; 
 int /*<<< orphan*/  initPlan ; 
 int /*<<< orphan*/  lefttree ; 
 int /*<<< orphan*/  parallel_aware ; 
 int /*<<< orphan*/  parallel_safe ; 
 int /*<<< orphan*/  plan_node_id ; 
 int /*<<< orphan*/  plan_rows ; 
 int /*<<< orphan*/  plan_width ; 
 int /*<<< orphan*/  qual ; 
 int /*<<< orphan*/  righttree ; 
 int /*<<< orphan*/  startup_cost ; 
 int /*<<< orphan*/  targetlist ; 
 int /*<<< orphan*/  total_cost ; 

__attribute__((used)) static void
ReadCommonPlan(Plan *local_node)
{
	READ_TEMP_LOCALS();

	READ_FLOAT_FIELD(startup_cost);
	READ_FLOAT_FIELD(total_cost);
	READ_FLOAT_FIELD(plan_rows);
	READ_INT_FIELD(plan_width);
	READ_BOOL_FIELD(parallel_aware);
	READ_BOOL_FIELD(parallel_safe);
	READ_INT_FIELD(plan_node_id);
	READ_NODE_FIELD(targetlist);
	READ_NODE_FIELD(qual);
	READ_NODE_FIELD(lefttree);
	READ_NODE_FIELD(righttree);
	READ_NODE_FIELD(initPlan);
	READ_BITMAPSET_FIELD(extParam);
	READ_BITMAPSET_FIELD(allParam);
}