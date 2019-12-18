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
typedef  int /*<<< orphan*/  SelectStmt ;

/* Variables and functions */
 int /*<<< orphan*/  SetOperation ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
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

__attribute__((used)) static void
_outSelectStmt(StringInfo str, const SelectStmt *node)
{
	WRITE_NODE_TYPE("SELECT");

	WRITE_NODE_FIELD(distinctClause);
	WRITE_NODE_FIELD(intoClause);
	WRITE_NODE_FIELD(targetList);
	WRITE_NODE_FIELD(fromClause);
	WRITE_NODE_FIELD(whereClause);
	WRITE_NODE_FIELD(groupClause);
	WRITE_NODE_FIELD(havingClause);
	WRITE_NODE_FIELD(windowClause);
	WRITE_NODE_FIELD(valuesLists);
	WRITE_NODE_FIELD(sortClause);
	WRITE_NODE_FIELD(limitOffset);
	WRITE_NODE_FIELD(limitCount);
	WRITE_NODE_FIELD(lockingClause);
	WRITE_NODE_FIELD(withClause);
	WRITE_ENUM_FIELD(op, SetOperation);
	WRITE_BOOL_FIELD(all);
	WRITE_NODE_FIELD(larg);
	WRITE_NODE_FIELD(rarg);
}