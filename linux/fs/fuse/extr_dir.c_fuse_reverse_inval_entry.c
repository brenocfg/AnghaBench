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
typedef  scalar_t__ u64 ;
struct super_block {int dummy; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  S_DEAD ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_dir_changed (struct inode*) ; 
 int /*<<< orphan*/  fuse_inode_eq ; 
 int /*<<< orphan*/  fuse_invalidate_entry (struct dentry*) ; 
 scalar_t__ get_node_id (struct inode*) ; 
 struct inode* ilookup5 (struct super_block*,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 

int fuse_reverse_inval_entry(struct super_block *sb, u64 parent_nodeid,
			     u64 child_nodeid, struct qstr *name)
{
	int err = -ENOTDIR;
	struct inode *parent;
	struct dentry *dir;
	struct dentry *entry;

	parent = ilookup5(sb, parent_nodeid, fuse_inode_eq, &parent_nodeid);
	if (!parent)
		return -ENOENT;

	inode_lock(parent);
	if (!S_ISDIR(parent->i_mode))
		goto unlock;

	err = -ENOENT;
	dir = d_find_alias(parent);
	if (!dir)
		goto unlock;

	name->hash = full_name_hash(dir, name->name, name->len);
	entry = d_lookup(dir, name);
	dput(dir);
	if (!entry)
		goto unlock;

	fuse_dir_changed(parent);
	fuse_invalidate_entry(entry);

	if (child_nodeid != 0 && d_really_is_positive(entry)) {
		inode_lock(d_inode(entry));
		if (get_node_id(d_inode(entry)) != child_nodeid) {
			err = -ENOENT;
			goto badentry;
		}
		if (d_mountpoint(entry)) {
			err = -EBUSY;
			goto badentry;
		}
		if (d_is_dir(entry)) {
			shrink_dcache_parent(entry);
			if (!simple_empty(entry)) {
				err = -ENOTEMPTY;
				goto badentry;
			}
			d_inode(entry)->i_flags |= S_DEAD;
		}
		dont_mount(entry);
		clear_nlink(d_inode(entry));
		err = 0;
 badentry:
		inode_unlock(d_inode(entry));
		if (!err)
			d_delete(entry);
	} else {
		err = 0;
	}
	dput(entry);

 unlock:
	inode_unlock(parent);
	iput(parent);
	return err;
}