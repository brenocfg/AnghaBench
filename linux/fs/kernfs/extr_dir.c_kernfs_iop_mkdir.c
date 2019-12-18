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
typedef  int /*<<< orphan*/  umode_t ;
struct kernfs_syscall_ops {int (* mkdir ) (struct kernfs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct kernfs_node {int dummy; } ;
struct inode {struct kernfs_node* i_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {struct kernfs_syscall_ops* syscall_ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  kernfs_get_active (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put_active (struct kernfs_node*) ; 
 TYPE_2__* kernfs_root (struct kernfs_node*) ; 
 int stub1 (struct kernfs_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kernfs_iop_mkdir(struct inode *dir, struct dentry *dentry,
			    umode_t mode)
{
	struct kernfs_node *parent = dir->i_private;
	struct kernfs_syscall_ops *scops = kernfs_root(parent)->syscall_ops;
	int ret;

	if (!scops || !scops->mkdir)
		return -EPERM;

	if (!kernfs_get_active(parent))
		return -ENODEV;

	ret = scops->mkdir(parent, dentry->d_name.name, mode);

	kernfs_put_active(parent);
	return ret;
}