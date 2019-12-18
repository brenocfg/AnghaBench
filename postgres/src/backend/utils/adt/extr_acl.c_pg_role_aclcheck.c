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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  AclResult ;
typedef  int AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NO_PRIV ; 
 int /*<<< orphan*/  ACLCHECK_OK ; 
 int ACL_CREATE ; 
 int ACL_GRANT_OPTION_FOR (int) ; 
 int ACL_USAGE ; 
 scalar_t__ has_privs_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_admin_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static AclResult
pg_role_aclcheck(Oid role_oid, Oid roleid, AclMode mode)
{
	if (mode & ACL_GRANT_OPTION_FOR(ACL_CREATE))
	{
		/*
		 * XXX For roleid == role_oid, is_admin_of_role() also examines the
		 * session and call stack.  That suits two-argument pg_has_role(), but
		 * it gives the three-argument version a lamentable whimsy.
		 */
		if (is_admin_of_role(roleid, role_oid))
			return ACLCHECK_OK;
	}
	if (mode & ACL_CREATE)
	{
		if (is_member_of_role(roleid, role_oid))
			return ACLCHECK_OK;
	}
	if (mode & ACL_USAGE)
	{
		if (has_privs_of_role(roleid, role_oid))
			return ACLCHECK_OK;
	}
	return ACLCHECK_NO_PRIV;
}