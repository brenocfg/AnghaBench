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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
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
_outPlanInfo(StringInfo str, const Plan *node)
{
	WRITE_FLOAT_FIELD(startup_cost, "%.2f");
	WRITE_FLOAT_FIELD(total_cost, "%.2f");
	WRITE_FLOAT_FIELD(plan_rows, "%.0f");
	WRITE_INT_FIELD(plan_width);
	WRITE_BOOL_FIELD(parallel_aware);
	WRITE_BOOL_FIELD(parallel_safe);
	WRITE_INT_FIELD(plan_node_id);
	WRITE_NODE_FIELD(targetlist);
	WRITE_NODE_FIELD(qual);
	WRITE_NODE_FIELD(lefttree);
	WRITE_NODE_FIELD(righttree);
	WRITE_NODE_FIELD(initPlan);
	WRITE_BITMAPSET_FIELD(extParam);
	WRITE_BITMAPSET_FIELD(allParam);
}