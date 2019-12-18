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
typedef  int /*<<< orphan*/  PlannedStmt ;

/* Variables and functions */
 int /*<<< orphan*/  CmdType ; 
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT64_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canSetTag ; 
 int /*<<< orphan*/  commandType ; 
 int /*<<< orphan*/  dependsOnRole ; 
 int /*<<< orphan*/  hasModifyingCTE ; 
 int /*<<< orphan*/  hasReturning ; 
 int /*<<< orphan*/  invalItems ; 
 int /*<<< orphan*/  jitFlags ; 
 int /*<<< orphan*/  parallelModeNeeded ; 
 int /*<<< orphan*/  paramExecTypes ; 
 int /*<<< orphan*/  planTree ; 
 int /*<<< orphan*/  queryId ; 
 int /*<<< orphan*/  relationOids ; 
 int /*<<< orphan*/  resultRelations ; 
 int /*<<< orphan*/  rewindPlanIDs ; 
 int /*<<< orphan*/  rootResultRelations ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  rtable ; 
 int /*<<< orphan*/  stmt_len ; 
 int /*<<< orphan*/  stmt_location ; 
 int /*<<< orphan*/  subplans ; 
 int /*<<< orphan*/  transientPlan ; 
 int /*<<< orphan*/  utilityStmt ; 

__attribute__((used)) static void
_outPlannedStmt(StringInfo str, const PlannedStmt *node)
{
	WRITE_NODE_TYPE("PLANNEDSTMT");

	WRITE_ENUM_FIELD(commandType, CmdType);
	WRITE_UINT64_FIELD(queryId);
	WRITE_BOOL_FIELD(hasReturning);
	WRITE_BOOL_FIELD(hasModifyingCTE);
	WRITE_BOOL_FIELD(canSetTag);
	WRITE_BOOL_FIELD(transientPlan);
	WRITE_BOOL_FIELD(dependsOnRole);
	WRITE_BOOL_FIELD(parallelModeNeeded);
	WRITE_INT_FIELD(jitFlags);
	WRITE_NODE_FIELD(planTree);
	WRITE_NODE_FIELD(rtable);
	WRITE_NODE_FIELD(resultRelations);
	WRITE_NODE_FIELD(rootResultRelations);
	WRITE_NODE_FIELD(subplans);
	WRITE_BITMAPSET_FIELD(rewindPlanIDs);
	WRITE_NODE_FIELD(rowMarks);
	WRITE_NODE_FIELD(relationOids);
	WRITE_NODE_FIELD(invalItems);
	WRITE_NODE_FIELD(paramExecTypes);
	WRITE_NODE_FIELD(utilityStmt);
	WRITE_LOCATION_FIELD(stmt_location);
	WRITE_LOCATION_FIELD(stmt_len);
}