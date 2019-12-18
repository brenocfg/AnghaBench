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
struct select_data {int /*<<< orphan*/  dispose; struct dentry* victim; struct dentry* start; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct dentry {int d_flags; TYPE_1__ d_lockref; } ;
typedef  enum d_walk_ret { ____Placeholder_d_walk_ret } d_walk_ret ;

/* Variables and functions */
 int DCACHE_LRU_LIST ; 
 int DCACHE_SHRINK_LIST ; 
 int D_WALK_CONTINUE ; 
 int D_WALK_NORETRY ; 
 int D_WALK_QUIT ; 
 int /*<<< orphan*/  d_lru_del (struct dentry*) ; 
 int /*<<< orphan*/  d_shrink_add (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 

__attribute__((used)) static enum d_walk_ret select_collect2(void *_data, struct dentry *dentry)
{
	struct select_data *data = _data;
	enum d_walk_ret ret = D_WALK_CONTINUE;

	if (data->start == dentry)
		goto out;

	if (dentry->d_flags & DCACHE_SHRINK_LIST) {
		if (!dentry->d_lockref.count) {
			rcu_read_lock();
			data->victim = dentry;
			return D_WALK_QUIT;
		}
	} else {
		if (dentry->d_flags & DCACHE_LRU_LIST)
			d_lru_del(dentry);
		if (!dentry->d_lockref.count)
			d_shrink_add(dentry, &data->dispose);
	}
	/*
	 * We can return to the caller if we have found some (this
	 * ensures forward progress). We'll be coming back to find
	 * the rest.
	 */
	if (!list_empty(&data->dispose))
		ret = need_resched() ? D_WALK_QUIT : D_WALK_NORETRY;
out:
	return ret;
}