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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_MOUNTED ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  d_unlinked (struct dentry*) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

int d_set_mounted(struct dentry *dentry)
{
	struct dentry *p;
	int ret = -ENOENT;
	write_seqlock(&rename_lock);
	for (p = dentry->d_parent; !IS_ROOT(p); p = p->d_parent) {
		/* Need exclusion wrt. d_invalidate() */
		spin_lock(&p->d_lock);
		if (unlikely(d_unhashed(p))) {
			spin_unlock(&p->d_lock);
			goto out;
		}
		spin_unlock(&p->d_lock);
	}
	spin_lock(&dentry->d_lock);
	if (!d_unlinked(dentry)) {
		ret = -EBUSY;
		if (!d_mountpoint(dentry)) {
			dentry->d_flags |= DCACHE_MOUNTED;
			ret = 0;
		}
	}
 	spin_unlock(&dentry->d_lock);
out:
	write_sequnlock(&rename_lock);
	return ret;
}