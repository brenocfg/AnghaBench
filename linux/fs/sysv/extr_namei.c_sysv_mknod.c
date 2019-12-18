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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int add_nondir (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  old_valid_dev (int /*<<< orphan*/ ) ; 
 struct inode* sysv_new_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysv_set_inode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysv_mknod(struct inode * dir, struct dentry * dentry, umode_t mode, dev_t rdev)
{
	struct inode * inode;
	int err;

	if (!old_valid_dev(rdev))
		return -EINVAL;

	inode = sysv_new_inode(dir, mode);
	err = PTR_ERR(inode);

	if (!IS_ERR(inode)) {
		sysv_set_inode(inode, rdev);
		mark_inode_dirty(inode);
		err = add_nondir(dentry, inode);
	}
	return err;
}