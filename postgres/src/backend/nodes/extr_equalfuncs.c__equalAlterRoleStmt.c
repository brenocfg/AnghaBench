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
typedef  int /*<<< orphan*/  AlterRoleStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  role ; 

__attribute__((used)) static bool
_equalAlterRoleStmt(const AlterRoleStmt *a, const AlterRoleStmt *b)
{
	COMPARE_NODE_FIELD(role);
	COMPARE_NODE_FIELD(options);
	COMPARE_SCALAR_FIELD(action);

	return true;
}