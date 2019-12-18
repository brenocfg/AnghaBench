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
struct page_counter {unsigned long max; } ;
struct mem_cgroup {struct page_counter memsw; struct page_counter memory; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drain_all_stock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_max_mutex ; 
 int /*<<< orphan*/  memcg_oom_recover (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int page_counter_set_max (struct page_counter*,unsigned long) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_free_mem_cgroup_pages (struct mem_cgroup*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mem_cgroup_resize_max(struct mem_cgroup *memcg,
				 unsigned long max, bool memsw)
{
	bool enlarge = false;
	bool drained = false;
	int ret;
	bool limits_invariant;
	struct page_counter *counter = memsw ? &memcg->memsw : &memcg->memory;

	do {
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}

		mutex_lock(&memcg_max_mutex);
		/*
		 * Make sure that the new limit (memsw or memory limit) doesn't
		 * break our basic invariant rule memory.max <= memsw.max.
		 */
		limits_invariant = memsw ? max >= memcg->memory.max :
					   max <= memcg->memsw.max;
		if (!limits_invariant) {
			mutex_unlock(&memcg_max_mutex);
			ret = -EINVAL;
			break;
		}
		if (max > counter->max)
			enlarge = true;
		ret = page_counter_set_max(counter, max);
		mutex_unlock(&memcg_max_mutex);

		if (!ret)
			break;

		if (!drained) {
			drain_all_stock(memcg);
			drained = true;
			continue;
		}

		if (!try_to_free_mem_cgroup_pages(memcg, 1,
					GFP_KERNEL, !memsw)) {
			ret = -EBUSY;
			break;
		}
	} while (true);

	if (!ret && enlarge)
		memcg_oom_recover(memcg);

	return ret;
}