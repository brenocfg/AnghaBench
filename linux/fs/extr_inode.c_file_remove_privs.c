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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_NOSEC (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int __remove_privs (struct dentry*,int) ; 
 int dentry_needs_remove_privs (struct dentry*) ; 
 struct dentry* file_dentry (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_has_no_xattr (struct inode*) ; 

int file_remove_privs(struct file *file)
{
	struct dentry *dentry = file_dentry(file);
	struct inode *inode = file_inode(file);
	int kill;
	int error = 0;

	/*
	 * Fast path for nothing security related.
	 * As well for non-regular files, e.g. blkdev inodes.
	 * For example, blkdev_write_iter() might get here
	 * trying to remove privs which it is not allowed to.
	 */
	if (IS_NOSEC(inode) || !S_ISREG(inode->i_mode))
		return 0;

	kill = dentry_needs_remove_privs(dentry);
	if (kill < 0)
		return kill;
	if (kill)
		error = __remove_privs(dentry, kill);
	if (!error)
		inode_has_no_xattr(inode);

	return error;
}