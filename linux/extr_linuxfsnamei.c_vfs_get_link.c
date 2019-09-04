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
struct inode {TYPE_1__* i_op; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct TYPE_2__ {char* (* get_link ) (struct dentry*,struct inode*,struct delayed_call*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_is_symlink (struct dentry*) ; 
 int /*<<< orphan*/  security_inode_readlink (struct dentry*) ; 
 char* stub1 (struct dentry*,struct inode*,struct delayed_call*) ; 

const char *vfs_get_link(struct dentry *dentry, struct delayed_call *done)
{
	const char *res = ERR_PTR(-EINVAL);
	struct inode *inode = d_inode(dentry);

	if (d_is_symlink(dentry)) {
		res = ERR_PTR(security_inode_readlink(dentry));
		if (!res)
			res = inode->i_op->get_link(dentry, inode, done);
	}
	return res;
}