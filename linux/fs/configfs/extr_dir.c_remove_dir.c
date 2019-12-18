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
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_remove_dirent (struct dentry*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static void remove_dir(struct dentry * d)
{
	struct dentry * parent = dget(d->d_parent);

	configfs_remove_dirent(d);

	if (d_really_is_positive(d))
		simple_rmdir(d_inode(parent),d);

	pr_debug(" o %pd removing done (%d)\n", d, d_count(d));

	dput(parent);
}