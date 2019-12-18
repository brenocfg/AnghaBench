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
struct TYPE_2__ {int (* mknod ) (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
 int S_IFCHR ; 
 int /*<<< orphan*/  WHITEOUT_DEV ; 
 int WHITEOUT_MODE ; 
 int may_create (struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,struct dentry*,int,int /*<<< orphan*/ ) ; 

int vfs_whiteout(struct inode *dir, struct dentry *dentry)
{
	int error = may_create(dir, dentry);
	if (error)
		return error;

	if (!dir->i_op->mknod)
		return -EPERM;

	return dir->i_op->mknod(dir, dentry,
				S_IFCHR | WHITEOUT_MODE, WHITEOUT_DEV);
}