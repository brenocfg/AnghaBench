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
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; TYPE_1__* d_op; scalar_t__ d_inode; int /*<<< orphan*/  d_lockref; struct dentry* d_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* d_release ) (struct dentry*) ;int /*<<< orphan*/  (* d_prune ) (struct dentry*) ;} ;

/* Variables and functions */
 int DCACHE_LRU_LIST ; 
 int DCACHE_MAY_FREE ; 
 int DCACHE_OP_PRUNE ; 
 int DCACHE_SHRINK_LIST ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  __d_drop (struct dentry*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  d_lru_del (struct dentry*) ; 
 int /*<<< orphan*/  dentry_free (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unlink_inode (struct dentry*) ; 
 int /*<<< orphan*/  dentry_unlist (struct dentry*,struct dentry*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockref_mark_dead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_dentry ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dentry*) ; 
 int /*<<< orphan*/  stub2 (struct dentry*) ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dentry_kill(struct dentry *dentry)
{
	struct dentry *parent = NULL;
	bool can_free = true;
	if (!IS_ROOT(dentry))
		parent = dentry->d_parent;

	/*
	 * The dentry is now unrecoverably dead to the world.
	 */
	lockref_mark_dead(&dentry->d_lockref);

	/*
	 * inform the fs via d_prune that this dentry is about to be
	 * unhashed and destroyed.
	 */
	if (dentry->d_flags & DCACHE_OP_PRUNE)
		dentry->d_op->d_prune(dentry);

	if (dentry->d_flags & DCACHE_LRU_LIST) {
		if (!(dentry->d_flags & DCACHE_SHRINK_LIST))
			d_lru_del(dentry);
	}
	/* if it was on the hash then remove it */
	__d_drop(dentry);
	dentry_unlist(dentry, parent);
	if (parent)
		spin_unlock(&parent->d_lock);
	if (dentry->d_inode)
		dentry_unlink_inode(dentry);
	else
		spin_unlock(&dentry->d_lock);
	this_cpu_dec(nr_dentry);
	if (dentry->d_op && dentry->d_op->d_release)
		dentry->d_op->d_release(dentry);

	spin_lock(&dentry->d_lock);
	if (dentry->d_flags & DCACHE_SHRINK_LIST) {
		dentry->d_flags |= DCACHE_MAY_FREE;
		can_free = false;
	}
	spin_unlock(&dentry->d_lock);
	if (likely(can_free))
		dentry_free(dentry);
	cond_resched();
}