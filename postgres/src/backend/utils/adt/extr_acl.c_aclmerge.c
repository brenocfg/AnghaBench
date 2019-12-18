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
typedef  int /*<<< orphan*/  AclItem ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/ * ACL_DAT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ACL_MODECHG_ADD ; 
 int ACL_NUM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/ * aclcopy (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * aclupdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

Acl *
aclmerge(const Acl *left_acl, const Acl *right_acl, Oid ownerId)
{
	Acl		   *result_acl;
	AclItem    *aip;
	int			i,
				num;

	/* Check for cases where one or both are empty/null */
	if (left_acl == NULL || ACL_NUM(left_acl) == 0)
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return NULL;
		else
			return aclcopy(right_acl);
	}
	else
	{
		if (right_acl == NULL || ACL_NUM(right_acl) == 0)
			return aclcopy(left_acl);
	}

	/* Merge them the hard way, one item at a time */
	result_acl = aclcopy(left_acl);

	aip = ACL_DAT(right_acl);
	num = ACL_NUM(right_acl);

	for (i = 0; i < num; i++, aip++)
	{
		Acl		   *tmp_acl;

		tmp_acl = aclupdate(result_acl, aip, ACL_MODECHG_ADD,
							ownerId, DROP_RESTRICT);
		pfree(result_acl);
		result_acl = tmp_acl;
	}

	return result_acl;
}