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
typedef  int /*<<< orphan*/  GrantRoleStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  admin_opt ; 
 int /*<<< orphan*/  behavior ; 
 int /*<<< orphan*/  granted_roles ; 
 int /*<<< orphan*/  grantee_roles ; 
 int /*<<< orphan*/  grantor ; 
 int /*<<< orphan*/  is_grant ; 

__attribute__((used)) static bool
_equalGrantRoleStmt(const GrantRoleStmt *a, const GrantRoleStmt *b)
{
	COMPARE_NODE_FIELD(granted_roles);
	COMPARE_NODE_FIELD(grantee_roles);
	COMPARE_SCALAR_FIELD(is_grant);
	COMPARE_SCALAR_FIELD(admin_opt);
	COMPARE_NODE_FIELD(grantor);
	COMPARE_SCALAR_FIELD(behavior);

	return true;
}