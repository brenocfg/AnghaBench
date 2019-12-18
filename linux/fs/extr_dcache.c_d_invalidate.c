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
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  d_walk (struct dentry*,struct dentry**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_mounts (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  find_submount ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void d_invalidate(struct dentry *dentry)
{
	bool had_submounts = false;
	spin_lock(&dentry->d_lock);
	if (d_unhashed(dentry)) {
		spin_unlock(&dentry->d_lock);
		return;
	}
	__d_drop(dentry);
	spin_unlock(&dentry->d_lock);

	/* Negative dentries can be dropped without further checks */
	if (!dentry->d_inode)
		return;

	shrink_dcache_parent(dentry);
	for (;;) {
		struct dentry *victim = NULL;
		d_walk(dentry, &victim, find_submount);
		if (!victim) {
			if (had_submounts)
				shrink_dcache_parent(dentry);
			return;
		}
		had_submounts = true;
		detach_mounts(victim);
		dput(victim);
	}
}