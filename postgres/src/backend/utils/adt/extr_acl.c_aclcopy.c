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
typedef  int /*<<< orphan*/  const Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_DAT (int /*<<< orphan*/  const*) ; 
 int ACL_NUM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* allocacl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Acl *
aclcopy(const Acl *orig_acl)
{
	Acl		   *result_acl;

	result_acl = allocacl(ACL_NUM(orig_acl));

	memcpy(ACL_DAT(result_acl),
		   ACL_DAT(orig_acl),
		   ACL_NUM(orig_acl) * sizeof(AclItem));

	return result_acl;
}