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
struct super_block {struct dentry* s_root; int /*<<< orphan*/  s_active; } ;
struct dentry {int /*<<< orphan*/  d_inode; void* d_fsdata; } ;
struct afs_net {struct super_block* dynroot_sb; } ;
struct afs_cell {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 

int afs_dynroot_mkdir(struct afs_net *net, struct afs_cell *cell)
{
	struct super_block *sb = net->dynroot_sb;
	struct dentry *root, *subdir;
	int ret;

	if (!sb || atomic_read(&sb->s_active) == 0)
		return 0;

	/* Let the ->lookup op do the creation */
	root = sb->s_root;
	inode_lock(root->d_inode);
	subdir = lookup_one_len(cell->name, root, cell->name_len);
	if (IS_ERR(subdir)) {
		ret = PTR_ERR(subdir);
		goto unlock;
	}

	/* Note that we're retaining an extra ref on the dentry */
	subdir->d_fsdata = (void *)1UL;
	ret = 0;
unlock:
	inode_unlock(root->d_inode);
	return ret;
}