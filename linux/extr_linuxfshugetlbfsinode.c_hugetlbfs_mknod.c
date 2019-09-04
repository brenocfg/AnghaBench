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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct inode* hugetlbfs_get_inode (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlbfs_mknod(struct inode *dir,
			struct dentry *dentry, umode_t mode, dev_t dev)
{
	struct inode *inode;
	int error = -ENOSPC;

	inode = hugetlbfs_get_inode(dir->i_sb, dir, mode, dev);
	if (inode) {
		dir->i_ctime = dir->i_mtime = current_time(dir);
		d_instantiate(dentry, inode);
		dget(dentry);	/* Extra count - pin the dentry in core */
		error = 0;
	}
	return error;
}