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
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int hfs_cat_delete (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int hfs_remove(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	int res;

	if (S_ISDIR(inode->i_mode) && inode->i_size != 2)
		return -ENOTEMPTY;
	res = hfs_cat_delete(inode->i_ino, dir, &dentry->d_name);
	if (res)
		return res;
	clear_nlink(inode);
	inode->i_ctime = current_time(inode);
	hfs_delete_inode(inode);
	mark_inode_dirty(inode);
	return 0;
}