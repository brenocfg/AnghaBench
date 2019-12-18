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
typedef  int /*<<< orphan*/  InsertStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cols ; 
 int /*<<< orphan*/  onConflictClause ; 
 int /*<<< orphan*/  override ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  returningList ; 
 int /*<<< orphan*/  selectStmt ; 
 int /*<<< orphan*/  withClause ; 

__attribute__((used)) static bool
_equalInsertStmt(const InsertStmt *a, const InsertStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(cols);
	COMPARE_NODE_FIELD(selectStmt);
	COMPARE_NODE_FIELD(onConflictClause);
	COMPARE_NODE_FIELD(returningList);
	COMPARE_NODE_FIELD(withClause);
	COMPARE_SCALAR_FIELD(override);

	return true;
}