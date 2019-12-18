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
typedef  int /*<<< orphan*/  AclItem ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_DAT (int /*<<< orphan*/  const*) ; 
 int ACL_NUM (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool
aclequal(const Acl *left_acl, const Acl *right_acl)
{
	/* Check for cases where one or both are empty/null */
	if (left_acl == NULL || ACL_NUM(left_acl) == 0)
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return true;
		else
			return false;
	}
	else
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return false;
	}

	if (ACL_NUM(left_acl) != ACL_NUM(right_acl))
		return false;

	if (memcmp(ACL_DAT(left_acl),
			   ACL_DAT(right_acl),
			   ACL_NUM(left_acl) * sizeof(AclItem)) == 0)
		return true;

	return false;
}