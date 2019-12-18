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
typedef  int /*<<< orphan*/  Query ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canSetTag ; 
 int /*<<< orphan*/  commandType ; 
 int /*<<< orphan*/  constraintDeps ; 
 int /*<<< orphan*/  cteList ; 
 int /*<<< orphan*/  distinctClause ; 
 int /*<<< orphan*/  groupClause ; 
 int /*<<< orphan*/  groupingSets ; 
 int /*<<< orphan*/  hasAggs ; 
 int /*<<< orphan*/  hasDistinctOn ; 
 int /*<<< orphan*/  hasForUpdate ; 
 int /*<<< orphan*/  hasModifyingCTE ; 
 int /*<<< orphan*/  hasRecursive ; 
 int /*<<< orphan*/  hasRowSecurity ; 
 int /*<<< orphan*/  hasSubLinks ; 
 int /*<<< orphan*/  hasTargetSRFs ; 
 int /*<<< orphan*/  hasWindowFuncs ; 
 int /*<<< orphan*/  havingQual ; 
 int /*<<< orphan*/  jointree ; 
 int /*<<< orphan*/  limitCount ; 
 int /*<<< orphan*/  limitOffset ; 
 int /*<<< orphan*/  onConflict ; 
 int /*<<< orphan*/  override ; 
 int /*<<< orphan*/  querySource ; 
 int /*<<< orphan*/  resultRelation ; 
 int /*<<< orphan*/  returningList ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  rtable ; 
 int /*<<< orphan*/  setOperations ; 
 int /*<<< orphan*/  sortClause ; 
 int /*<<< orphan*/  stmt_len ; 
 int /*<<< orphan*/  stmt_location ; 
 int /*<<< orphan*/  targetList ; 
 int /*<<< orphan*/  utilityStmt ; 
 int /*<<< orphan*/  windowClause ; 
 int /*<<< orphan*/  withCheckOptions ; 

__attribute__((used)) static bool
_equalQuery(const Query *a, const Query *b)
{
	COMPARE_SCALAR_FIELD(commandType);
	COMPARE_SCALAR_FIELD(querySource);
	/* we intentionally ignore queryId, since it might not be set */
	COMPARE_SCALAR_FIELD(canSetTag);
	COMPARE_NODE_FIELD(utilityStmt);
	COMPARE_SCALAR_FIELD(resultRelation);
	COMPARE_SCALAR_FIELD(hasAggs);
	COMPARE_SCALAR_FIELD(hasWindowFuncs);
	COMPARE_SCALAR_FIELD(hasTargetSRFs);
	COMPARE_SCALAR_FIELD(hasSubLinks);
	COMPARE_SCALAR_FIELD(hasDistinctOn);
	COMPARE_SCALAR_FIELD(hasRecursive);
	COMPARE_SCALAR_FIELD(hasModifyingCTE);
	COMPARE_SCALAR_FIELD(hasForUpdate);
	COMPARE_SCALAR_FIELD(hasRowSecurity);
	COMPARE_NODE_FIELD(cteList);
	COMPARE_NODE_FIELD(rtable);
	COMPARE_NODE_FIELD(jointree);
	COMPARE_NODE_FIELD(targetList);
	COMPARE_SCALAR_FIELD(override);
	COMPARE_NODE_FIELD(onConflict);
	COMPARE_NODE_FIELD(returningList);
	COMPARE_NODE_FIELD(groupClause);
	COMPARE_NODE_FIELD(groupingSets);
	COMPARE_NODE_FIELD(havingQual);
	COMPARE_NODE_FIELD(windowClause);
	COMPARE_NODE_FIELD(distinctClause);
	COMPARE_NODE_FIELD(sortClause);
	COMPARE_NODE_FIELD(limitOffset);
	COMPARE_NODE_FIELD(limitCount);
	COMPARE_NODE_FIELD(rowMarks);
	COMPARE_NODE_FIELD(setOperations);
	COMPARE_NODE_FIELD(constraintDeps);
	COMPARE_NODE_FIELD(withCheckOptions);
	COMPARE_LOCATION_FIELD(stmt_location);
	COMPARE_LOCATION_FIELD(stmt_len);

	return true;
}