#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct posix_acl {int dummy; } ;
struct inode {TYPE_2__* i_op; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int (* set_acl ) (struct inode*,struct posix_acl*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  s_user_ns; } ;

/* Variables and functions */
 int ACL_TYPE_DEFAULT ; 
 int EACCES ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_POSIXACL (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_owner_or_capable (struct inode*) ; 
 int posix_acl_valid (int /*<<< orphan*/ ,struct posix_acl*) ; 
 int stub1 (struct inode*,struct posix_acl*,int) ; 

int
set_posix_acl(struct inode *inode, int type, struct posix_acl *acl)
{
	if (!IS_POSIXACL(inode))
		return -EOPNOTSUPP;
	if (!inode->i_op->set_acl)
		return -EOPNOTSUPP;

	if (type == ACL_TYPE_DEFAULT && !S_ISDIR(inode->i_mode))
		return acl ? -EACCES : 0;
	if (!inode_owner_or_capable(inode))
		return -EPERM;

	if (acl) {
		int ret = posix_acl_valid(inode->i_sb->s_user_ns, acl);
		if (ret)
			return ret;
	}
	return inode->i_op->set_acl(inode, acl, type);
}