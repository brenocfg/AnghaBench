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
struct select_data {int /*<<< orphan*/  dispose; struct dentry* victim; int /*<<< orphan*/  found; struct dentry* start; } ;
struct dentry {struct dentry* d_parent; int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dentry_kill (struct dentry*) ; 
 int /*<<< orphan*/  __dput_to_list (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  d_walk (struct dentry*,struct select_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  select_collect ; 
 int /*<<< orphan*/  select_collect2 ; 
 int /*<<< orphan*/  shrink_dentry_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shrink_lock_dentry (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void shrink_dcache_parent(struct dentry *parent)
{
	for (;;) {
		struct select_data data = {.start = parent};

		INIT_LIST_HEAD(&data.dispose);
		d_walk(parent, &data, select_collect);

		if (!list_empty(&data.dispose)) {
			shrink_dentry_list(&data.dispose);
			continue;
		}

		cond_resched();
		if (!data.found)
			break;
		data.victim = NULL;
		d_walk(parent, &data, select_collect2);
		if (data.victim) {
			struct dentry *parent;
			spin_lock(&data.victim->d_lock);
			if (!shrink_lock_dentry(data.victim)) {
				spin_unlock(&data.victim->d_lock);
				rcu_read_unlock();
			} else {
				rcu_read_unlock();
				parent = data.victim->d_parent;
				if (parent != data.victim)
					__dput_to_list(parent, &data.dispose);
				__dentry_kill(data.victim);
			}
		}
		if (!list_empty(&data.dispose))
			shrink_dentry_list(&data.dispose);
	}
}