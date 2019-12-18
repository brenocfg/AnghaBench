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
typedef  int /*<<< orphan*/  AlterTableMoveAllStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_tablespacename ; 
 int /*<<< orphan*/  nowait ; 
 int /*<<< orphan*/  objtype ; 
 int /*<<< orphan*/  orig_tablespacename ; 
 int /*<<< orphan*/  roles ; 

__attribute__((used)) static bool
_equalAlterTableMoveAllStmt(const AlterTableMoveAllStmt *a,
							const AlterTableMoveAllStmt *b)
{
	COMPARE_STRING_FIELD(orig_tablespacename);
	COMPARE_SCALAR_FIELD(objtype);
	COMPARE_NODE_FIELD(roles);
	COMPARE_STRING_FIELD(new_tablespacename);
	COMPARE_SCALAR_FIELD(nowait);

	return true;
}