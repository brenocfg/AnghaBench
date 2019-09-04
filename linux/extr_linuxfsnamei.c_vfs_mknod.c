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
struct inode {TYPE_1__* i_op; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int (* mknod ) (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MKNOD ; 
 int EPERM ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int devcgroup_inode_mknod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 
 int may_create (struct inode*,struct dentry*) ; 
 int security_inode_mknod (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
{
	int error = may_create(dir, dentry);

	if (error)
		return error;

	if ((S_ISCHR(mode) || S_ISBLK(mode)) && !capable(CAP_MKNOD))
		return -EPERM;

	if (!dir->i_op->mknod)
		return -EPERM;

	error = devcgroup_inode_mknod(mode, dev);
	if (error)
		return error;

	error = security_inode_mknod(dir, dentry, mode, dev);
	if (error)
		return error;

	error = dir->i_op->mknod(dir, dentry, mode, dev);
	if (!error)
		fsnotify_create(dir, dentry);
	return error;
}