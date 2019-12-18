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
struct inode {int /*<<< orphan*/  i_ctime; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RENAME_NOREPLACE ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int omfs_add_link (struct dentry*,struct inode*) ; 
 int omfs_delete_entry (struct dentry*) ; 
 int omfs_remove (struct inode*,struct dentry*) ; 

__attribute__((used)) static int omfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		       struct inode *new_dir, struct dentry *new_dentry,
		       unsigned int flags)
{
	struct inode *new_inode = d_inode(new_dentry);
	struct inode *old_inode = d_inode(old_dentry);
	int err;

	if (flags & ~RENAME_NOREPLACE)
		return -EINVAL;

	if (new_inode) {
		/* overwriting existing file/dir */
		err = omfs_remove(new_dir, new_dentry);
		if (err)
			goto out;
	}

	/* since omfs locates files by name, we need to unlink _before_
	 * adding the new link or we won't find the old one */
	err = omfs_delete_entry(old_dentry);
	if (err)
		goto out;

	mark_inode_dirty(old_dir);
	err = omfs_add_link(new_dentry, old_inode);
	if (err)
		goto out;

	old_inode->i_ctime = current_time(old_inode);
	mark_inode_dirty(old_inode);
out:
	return err;
}