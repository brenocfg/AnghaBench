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
struct qstr {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct dentry {int /*<<< orphan*/  d_sb; struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int ovl_cleanup (struct inode*,struct dentry*) ; 
 int ovl_cleanup_and_whiteout (struct dentry*,struct inode*,struct dentry*) ; 
 struct dentry* ovl_dentry_lower (struct dentry*) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 int ovl_get_index_name (struct dentry*,struct qstr*) ; 
 scalar_t__ ovl_index_all (int /*<<< orphan*/ ) ; 
 struct dentry* ovl_indexdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_set_nlink_upper (struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*,struct dentry*,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static void ovl_cleanup_index(struct dentry *dentry)
{
	struct dentry *indexdir = ovl_indexdir(dentry->d_sb);
	struct inode *dir = indexdir->d_inode;
	struct dentry *lowerdentry = ovl_dentry_lower(dentry);
	struct dentry *upperdentry = ovl_dentry_upper(dentry);
	struct dentry *index = NULL;
	struct inode *inode;
	struct qstr name = { };
	int err;

	err = ovl_get_index_name(lowerdentry, &name);
	if (err)
		goto fail;

	inode = d_inode(upperdentry);
	if (!S_ISDIR(inode->i_mode) && inode->i_nlink != 1) {
		pr_warn_ratelimited("overlayfs: cleanup linked index (%pd2, ino=%lu, nlink=%u)\n",
				    upperdentry, inode->i_ino, inode->i_nlink);
		/*
		 * We either have a bug with persistent union nlink or a lower
		 * hardlink was added while overlay is mounted. Adding a lower
		 * hardlink and then unlinking all overlay hardlinks would drop
		 * overlay nlink to zero before all upper inodes are unlinked.
		 * As a safety measure, when that situation is detected, set
		 * the overlay nlink to the index inode nlink minus one for the
		 * index entry itself.
		 */
		set_nlink(d_inode(dentry), inode->i_nlink - 1);
		ovl_set_nlink_upper(dentry);
		goto out;
	}

	inode_lock_nested(dir, I_MUTEX_PARENT);
	index = lookup_one_len(name.name, indexdir, name.len);
	err = PTR_ERR(index);
	if (IS_ERR(index)) {
		index = NULL;
	} else if (ovl_index_all(dentry->d_sb)) {
		/* Whiteout orphan index to block future open by handle */
		err = ovl_cleanup_and_whiteout(indexdir, dir, index);
	} else {
		/* Cleanup orphan index entries */
		err = ovl_cleanup(dir, index);
	}

	inode_unlock(dir);
	if (err)
		goto fail;

out:
	kfree(name.name);
	dput(index);
	return;

fail:
	pr_err("overlayfs: cleanup index of '%pd2' failed (%i)\n", dentry, err);
	goto out;
}