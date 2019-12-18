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
typedef  int /*<<< orphan*/  AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmds ; 
 int /*<<< orphan*/  missing_ok ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  relkind ; 

__attribute__((used)) static bool
_equalAlterTableStmt(const AlterTableStmt *a, const AlterTableStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(cmds);
	COMPARE_SCALAR_FIELD(relkind);
	COMPARE_SCALAR_FIELD(missing_ok);

	return true;
}