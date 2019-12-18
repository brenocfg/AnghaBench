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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  aafs_count ; 
 int /*<<< orphan*/  aafs_mnt ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_rmdir (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static void aafs_remove(struct dentry *dentry)
{
	struct inode *dir;

	if (!dentry || IS_ERR(dentry))
		return;

	dir = d_inode(dentry->d_parent);
	inode_lock(dir);
	if (simple_positive(dentry)) {
		if (d_is_dir(dentry))
			simple_rmdir(dir, dentry);
		else
			simple_unlink(dir, dentry);
		d_delete(dentry);
		dput(dentry);
	}
	inode_unlock(dir);
	simple_release_fs(&aafs_mnt, &aafs_count);
}