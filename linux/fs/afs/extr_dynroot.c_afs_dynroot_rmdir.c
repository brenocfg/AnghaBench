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
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/ * d_fsdata; } ;
struct afs_net {struct super_block* dynroot_sb; } ;
struct afs_cell {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  _debug (char*,struct dentry*,...) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* try_lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 

void afs_dynroot_rmdir(struct afs_net *net, struct afs_cell *cell)
{
	struct super_block *sb = net->dynroot_sb;
	struct dentry *root, *subdir;

	if (!sb || atomic_read(&sb->s_active) == 0)
		return;

	root = sb->s_root;
	inode_lock(root->d_inode);

	/* Don't want to trigger a lookup call, which will re-add the cell */
	subdir = try_lookup_one_len(cell->name, root, cell->name_len);
	if (IS_ERR_OR_NULL(subdir)) {
		_debug("lookup %ld", PTR_ERR(subdir));
		goto no_dentry;
	}

	_debug("rmdir %pd %u", subdir, d_count(subdir));

	if (subdir->d_fsdata) {
		_debug("unpin %u", d_count(subdir));
		subdir->d_fsdata = NULL;
		dput(subdir);
	}
	dput(subdir);
no_dentry:
	inode_unlock(root->d_inode);
	_leave("");
}