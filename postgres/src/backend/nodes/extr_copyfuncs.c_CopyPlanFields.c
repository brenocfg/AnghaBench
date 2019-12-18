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
 int /*<<< orphan*/  COPY_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
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
CopyPlanFields(const Plan *from, Plan *newnode)
{
	COPY_SCALAR_FIELD(startup_cost);
	COPY_SCALAR_FIELD(total_cost);
	COPY_SCALAR_FIELD(plan_rows);
	COPY_SCALAR_FIELD(plan_width);
	COPY_SCALAR_FIELD(parallel_aware);
	COPY_SCALAR_FIELD(parallel_safe);
	COPY_SCALAR_FIELD(plan_node_id);
	COPY_NODE_FIELD(targetlist);
	COPY_NODE_FIELD(qual);
	COPY_NODE_FIELD(lefttree);
	COPY_NODE_FIELD(righttree);
	COPY_NODE_FIELD(initPlan);
	COPY_BITMAPSET_FIELD(extParam);
	COPY_BITMAPSET_FIELD(allParam);
}