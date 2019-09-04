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
struct kernfs_syscall_ops {int (* rename ) (struct kernfs_node*,struct kernfs_node*,int /*<<< orphan*/ ) ;} ;
struct kernfs_node {int dummy; } ;
struct inode {struct kernfs_node* i_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {struct kernfs_syscall_ops* syscall_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 struct kernfs_node* kernfs_dentry_node (struct dentry*) ; 
 int /*<<< orphan*/  kernfs_get_active (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put_active (struct kernfs_node*) ; 
 TYPE_2__* kernfs_root (struct kernfs_node*) ; 
 int stub1 (struct kernfs_node*,struct kernfs_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kernfs_iop_rename(struct inode *old_dir, struct dentry *old_dentry,
			     struct inode *new_dir, struct dentry *new_dentry,
			     unsigned int flags)
{
	struct kernfs_node *kn = kernfs_dentry_node(old_dentry);
	struct kernfs_node *new_parent = new_dir->i_private;
	struct kernfs_syscall_ops *scops = kernfs_root(kn)->syscall_ops;
	int ret;

	if (flags)
		return -EINVAL;

	if (!scops || !scops->rename)
		return -EPERM;

	if (!kernfs_get_active(kn))
		return -ENODEV;

	if (!kernfs_get_active(new_parent)) {
		kernfs_put_active(kn);
		return -ENODEV;
	}

	ret = scops->rename(kn, new_parent, new_dentry->d_name.name);

	kernfs_put_active(new_parent);
	kernfs_put_active(kn);
	return ret;
}