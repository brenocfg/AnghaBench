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
typedef  int /*<<< orphan*/  SetOperationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all ; 
 int /*<<< orphan*/  colCollations ; 
 int /*<<< orphan*/  colTypes ; 
 int /*<<< orphan*/  colTypmods ; 
 int /*<<< orphan*/  groupClauses ; 
 int /*<<< orphan*/  larg ; 
 int /*<<< orphan*/  op ; 
 int /*<<< orphan*/  rarg ; 

__attribute__((used)) static bool
_equalSetOperationStmt(const SetOperationStmt *a, const SetOperationStmt *b)
{
	COMPARE_SCALAR_FIELD(op);
	COMPARE_SCALAR_FIELD(all);
	COMPARE_NODE_FIELD(larg);
	COMPARE_NODE_FIELD(rarg);
	COMPARE_NODE_FIELD(colTypes);
	COMPARE_NODE_FIELD(colTypmods);
	COMPARE_NODE_FIELD(colCollations);
	COMPARE_NODE_FIELD(groupClauses);

	return true;
}