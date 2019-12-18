#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
struct inode {TYPE_1__* i_op; } ;
struct TYPE_2__ {int (* set_acl ) (struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int EOPNOTSUPP ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct posix_acl*) ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int __posix_acl_chmod (struct posix_acl**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct posix_acl* get_acl (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int stub1 (struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ; 

int
posix_acl_chmod(struct inode *inode, umode_t mode)
{
	struct posix_acl *acl;
	int ret = 0;

	if (!IS_POSIXACL(inode))
		return 0;
	if (!inode->i_op->set_acl)
		return -EOPNOTSUPP;

	acl = get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR_OR_NULL(acl)) {
		if (acl == ERR_PTR(-EOPNOTSUPP))
			return 0;
		return PTR_ERR(acl);
	}

	ret = __posix_acl_chmod(&acl, GFP_KERNEL, mode);
	if (ret)
		return ret;
	ret = inode->i_op->set_acl(inode, acl, ACL_TYPE_ACCESS);
	posix_acl_release(acl);
	return ret;
}