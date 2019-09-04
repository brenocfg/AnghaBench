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
struct dentry {struct configfs_dirent* d_fsdata; int /*<<< orphan*/  d_parent; } ;
struct configfs_dirent {int /*<<< orphan*/  s_sibling; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_dir(struct dentry * d)
{
	struct dentry * parent = dget(d->d_parent);
	struct configfs_dirent * sd;

	sd = d->d_fsdata;
	spin_lock(&configfs_dirent_lock);
	list_del_init(&sd->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	configfs_put(sd);
	if (d_really_is_positive(d))
		simple_rmdir(d_inode(parent),d);

	pr_debug(" o %pd removing done (%d)\n", d, d_count(d));

	dput(parent);
}