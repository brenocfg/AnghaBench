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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __debugfs_file_removed (struct dentry*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 scalar_t__ d_is_reg (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_unlink (int /*<<< orphan*/ ,struct dentry*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int simple_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static int __debugfs_remove(struct dentry *dentry, struct dentry *parent)
{
	int ret = 0;

	if (simple_positive(dentry)) {
		dget(dentry);
		if (d_is_dir(dentry)) {
			ret = simple_rmdir(d_inode(parent), dentry);
			if (!ret)
				fsnotify_rmdir(d_inode(parent), dentry);
		} else {
			simple_unlink(d_inode(parent), dentry);
			fsnotify_unlink(d_inode(parent), dentry);
		}
		if (!ret)
			d_delete(dentry);
		if (d_is_reg(dentry))
			__debugfs_file_removed(dentry);
		dput(dentry);
	}
	return ret;
}