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
typedef  int /*<<< orphan*/  SelectStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all ; 
 int /*<<< orphan*/  distinctClause ; 
 int /*<<< orphan*/  fromClause ; 
 int /*<<< orphan*/  groupClause ; 
 int /*<<< orphan*/  havingClause ; 
 int /*<<< orphan*/  intoClause ; 
 int /*<<< orphan*/  larg ; 
 int /*<<< orphan*/  limitCount ; 
 int /*<<< orphan*/  limitOffset ; 
 int /*<<< orphan*/  lockingClause ; 
 int /*<<< orphan*/  op ; 
 int /*<<< orphan*/  rarg ; 
 int /*<<< orphan*/  sortClause ; 
 int /*<<< orphan*/  targetList ; 
 int /*<<< orphan*/  valuesLists ; 
 int /*<<< orphan*/  whereClause ; 
 int /*<<< orphan*/  windowClause ; 
 int /*<<< orphan*/  withClause ; 

__attribute__((used)) static bool
_equalSelectStmt(const SelectStmt *a, const SelectStmt *b)
{
	COMPARE_NODE_FIELD(distinctClause);
	COMPARE_NODE_FIELD(intoClause);
	COMPARE_NODE_FIELD(targetList);
	COMPARE_NODE_FIELD(fromClause);
	COMPARE_NODE_FIELD(whereClause);
	COMPARE_NODE_FIELD(groupClause);
	COMPARE_NODE_FIELD(havingClause);
	COMPARE_NODE_FIELD(windowClause);
	COMPARE_NODE_FIELD(valuesLists);
	COMPARE_NODE_FIELD(sortClause);
	COMPARE_NODE_FIELD(limitOffset);
	COMPARE_NODE_FIELD(limitCount);
	COMPARE_NODE_FIELD(lockingClause);
	COMPARE_NODE_FIELD(withClause);
	COMPARE_SCALAR_FIELD(op);
	COMPARE_SCALAR_FIELD(all);
	COMPARE_NODE_FIELD(larg);
	COMPARE_NODE_FIELD(rarg);

	return true;
}