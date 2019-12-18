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
struct dentry {int /*<<< orphan*/  d_lock; } ;
struct configfs_dirent {struct dentry* s_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget_dlock (struct dentry*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void configfs_drop_dentry(struct configfs_dirent * sd, struct dentry * parent)
{
	struct dentry * dentry = sd->s_dentry;

	if (dentry) {
		spin_lock(&dentry->d_lock);
		if (simple_positive(dentry)) {
			dget_dlock(dentry);
			__d_drop(dentry);
			spin_unlock(&dentry->d_lock);
			simple_unlink(d_inode(parent), dentry);
		} else
			spin_unlock(&dentry->d_lock);
	}
}