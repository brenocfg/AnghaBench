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
 int EIO ; 
 int /*<<< orphan*/ * lock_rename (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 

int ovl_lock_rename_workdir(struct dentry *workdir, struct dentry *upperdir)
{
	/* Workdir should not be the same as upperdir */
	if (workdir == upperdir)
		goto err;

	/* Workdir should not be subdir of upperdir and vice versa */
	if (lock_rename(workdir, upperdir) != NULL)
		goto err_unlock;

	return 0;

err_unlock:
	unlock_rename(workdir, upperdir);
err:
	pr_err("overlayfs: failed to lock workdir+upperdir\n");
	return -EIO;
}