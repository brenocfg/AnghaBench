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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ACL_ID_PUBLIC ; 
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ has_privs_of_role (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
check_role_for_policy(ArrayType *policy_roles, Oid user_id)
{
	int			i;
	Oid		   *roles = (Oid *) ARR_DATA_PTR(policy_roles);

	/* Quick fall-thru for policies applied to all roles */
	if (roles[0] == ACL_ID_PUBLIC)
		return true;

	for (i = 0; i < ARR_DIMS(policy_roles)[0]; i++)
	{
		if (has_privs_of_role(user_id, roles[i]))
			return true;
	}

	return false;
}