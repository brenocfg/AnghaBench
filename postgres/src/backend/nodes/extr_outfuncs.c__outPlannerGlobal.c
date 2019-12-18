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
typedef  int /*<<< orphan*/  PlannerGlobal ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CHAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dependsOnRole ; 
 int /*<<< orphan*/  finalrowmarks ; 
 int /*<<< orphan*/  finalrtable ; 
 int /*<<< orphan*/  invalItems ; 
 int /*<<< orphan*/  lastPHId ; 
 int /*<<< orphan*/  lastPlanNodeId ; 
 int /*<<< orphan*/  lastRowMarkId ; 
 int /*<<< orphan*/  maxParallelHazard ; 
 int /*<<< orphan*/  parallelModeNeeded ; 
 int /*<<< orphan*/  parallelModeOK ; 
 int /*<<< orphan*/  paramExecTypes ; 
 int /*<<< orphan*/  relationOids ; 
 int /*<<< orphan*/  resultRelations ; 
 int /*<<< orphan*/  rewindPlanIDs ; 
 int /*<<< orphan*/  rootResultRelations ; 
 int /*<<< orphan*/  subplans ; 
 int /*<<< orphan*/  transientPlan ; 

__attribute__((used)) static void
_outPlannerGlobal(StringInfo str, const PlannerGlobal *node)
{
	WRITE_NODE_TYPE("PLANNERGLOBAL");

	/* NB: this isn't a complete set of fields */
	WRITE_NODE_FIELD(subplans);
	WRITE_BITMAPSET_FIELD(rewindPlanIDs);
	WRITE_NODE_FIELD(finalrtable);
	WRITE_NODE_FIELD(finalrowmarks);
	WRITE_NODE_FIELD(resultRelations);
	WRITE_NODE_FIELD(rootResultRelations);
	WRITE_NODE_FIELD(relationOids);
	WRITE_NODE_FIELD(invalItems);
	WRITE_NODE_FIELD(paramExecTypes);
	WRITE_UINT_FIELD(lastPHId);
	WRITE_UINT_FIELD(lastRowMarkId);
	WRITE_INT_FIELD(lastPlanNodeId);
	WRITE_BOOL_FIELD(transientPlan);
	WRITE_BOOL_FIELD(dependsOnRole);
	WRITE_BOOL_FIELD(parallelModeOK);
	WRITE_BOOL_FIELD(parallelModeNeeded);
	WRITE_CHAR_FIELD(maxParallelHazard);
}