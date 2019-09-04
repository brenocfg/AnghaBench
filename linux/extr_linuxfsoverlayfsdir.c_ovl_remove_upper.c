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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_parent; TYPE_1__ d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_clear_empty (struct dentry*,struct list_head*) ; 
 struct dentry* ovl_dentry_upper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dir_modified (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_matches_upper (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  ovl_type_origin (struct dentry*) ; 
 int vfs_rmdir (struct inode*,struct dentry*) ; 
 int vfs_unlink (struct inode*,struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_remove_upper(struct dentry *dentry, bool is_dir,
			    struct list_head *list)
{
	struct dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	struct inode *dir = upperdir->d_inode;
	struct dentry *upper;
	struct dentry *opaquedir = NULL;
	int err;

	if (!list_empty(list)) {
		opaquedir = ovl_clear_empty(dentry, list);
		err = PTR_ERR(opaquedir);
		if (IS_ERR(opaquedir))
			goto out;
	}

	inode_lock_nested(dir, I_MUTEX_PARENT);
	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	if (IS_ERR(upper))
		goto out_unlock;

	err = -ESTALE;
	if ((opaquedir && upper != opaquedir) ||
	    (!opaquedir && !ovl_matches_upper(dentry, upper)))
		goto out_dput_upper;

	if (is_dir)
		err = vfs_rmdir(dir, upper);
	else
		err = vfs_unlink(dir, upper, NULL);
	ovl_dir_modified(dentry->d_parent, ovl_type_origin(dentry));

	/*
	 * Keeping this dentry hashed would mean having to release
	 * upperpath/lowerpath, which could only be done if we are the
	 * sole user of this dentry.  Too tricky...  Just unhash for
	 * now.
	 */
	if (!err)
		d_drop(dentry);
out_dput_upper:
	dput(upper);
out_unlock:
	inode_unlock(dir);
	dput(opaquedir);
out:
	return err;
}