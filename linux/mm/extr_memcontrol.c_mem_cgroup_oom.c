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
struct mem_cgroup {int /*<<< orphan*/  css; scalar_t__ oom_kill_disable; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum oom_status { ____Placeholder_oom_status } oom_status ;
struct TYPE_2__ {int memcg_oom_order; int /*<<< orphan*/  memcg_oom_gfp_mask; struct mem_cgroup* memcg_in_oom; int /*<<< orphan*/  in_user_fault; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_OOM ; 
 int OOM_ASYNC ; 
 int OOM_FAILED ; 
 int OOM_SKIPPED ; 
 int OOM_SUCCESS ; 
 int PAGE_ALLOC_COSTLY_ORDER ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  mem_cgroup_mark_under_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_notify (struct mem_cgroup*) ; 
 int mem_cgroup_oom_trylock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_unlock (struct mem_cgroup*) ; 
 scalar_t__ mem_cgroup_out_of_memory (struct mem_cgroup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mem_cgroup_unmark_under_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_memory_event (struct mem_cgroup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum oom_status mem_cgroup_oom(struct mem_cgroup *memcg, gfp_t mask, int order)
{
	enum oom_status ret;
	bool locked;

	if (order > PAGE_ALLOC_COSTLY_ORDER)
		return OOM_SKIPPED;

	memcg_memory_event(memcg, MEMCG_OOM);

	/*
	 * We are in the middle of the charge context here, so we
	 * don't want to block when potentially sitting on a callstack
	 * that holds all kinds of filesystem and mm locks.
	 *
	 * cgroup1 allows disabling the OOM killer and waiting for outside
	 * handling until the charge can succeed; remember the context and put
	 * the task to sleep at the end of the page fault when all locks are
	 * released.
	 *
	 * On the other hand, in-kernel OOM killer allows for an async victim
	 * memory reclaim (oom_reaper) and that means that we are not solely
	 * relying on the oom victim to make a forward progress and we can
	 * invoke the oom killer here.
	 *
	 * Please note that mem_cgroup_out_of_memory might fail to find a
	 * victim and then we have to bail out from the charge path.
	 */
	if (memcg->oom_kill_disable) {
		if (!current->in_user_fault)
			return OOM_SKIPPED;
		css_get(&memcg->css);
		current->memcg_in_oom = memcg;
		current->memcg_oom_gfp_mask = mask;
		current->memcg_oom_order = order;

		return OOM_ASYNC;
	}

	mem_cgroup_mark_under_oom(memcg);

	locked = mem_cgroup_oom_trylock(memcg);

	if (locked)
		mem_cgroup_oom_notify(memcg);

	mem_cgroup_unmark_under_oom(memcg);
	if (mem_cgroup_out_of_memory(memcg, mask, order))
		ret = OOM_SUCCESS;
	else
		ret = OOM_FAILED;

	if (locked)
		mem_cgroup_oom_unlock(memcg);

	return ret;
}