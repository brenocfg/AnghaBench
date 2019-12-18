#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page_counter {int dummy; } ;
struct mem_cgroup {scalar_t__ high; int /*<<< orphan*/  high_work; int /*<<< orphan*/  memory; int /*<<< orphan*/  css; int /*<<< orphan*/  memsw; } ;
typedef  int gfp_t ;
typedef  enum oom_status { ____Placeholder_oom_status } oom_status ;
struct TYPE_5__ {int flags; unsigned int memcg_nr_pages_over_high; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MEMCG_CHARGE_BATCH ; 
 int /*<<< orphan*/  MEMCG_MAX ; 
 int MEM_CGROUP_RECLAIM_RETRIES ; 
#define  OOM_FAILED 129 
#define  OOM_SUCCESS 128 
 int PAGE_ALLOC_COSTLY_ORDER ; 
 unsigned int PAGE_SIZE ; 
 int PF_MEMALLOC ; 
 int __GFP_ATOMIC ; 
 int __GFP_NOFAIL ; 
 int __GFP_NORETRY ; 
 int __GFP_RETRY_MAYFAIL ; 
 scalar_t__ consume_stock (struct mem_cgroup*,unsigned int) ; 
 int /*<<< orphan*/  css_get_many (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__* current ; 
 scalar_t__ do_memsw_account () ; 
 int /*<<< orphan*/  drain_all_stock (struct mem_cgroup*) ; 
 scalar_t__ fatal_signal_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  get_order (unsigned int) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int) ; 
 scalar_t__ in_interrupt () ; 
 unsigned int max (int /*<<< orphan*/ ,unsigned int) ; 
 struct mem_cgroup* mem_cgroup_from_counter (struct page_counter*,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_cgroup_is_root (struct mem_cgroup*) ; 
 unsigned int mem_cgroup_margin (struct mem_cgroup*) ; 
 int mem_cgroup_oom (struct mem_cgroup*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_cgroup_wait_acct_move (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_memory_event (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory ; 
 int /*<<< orphan*/  memsw ; 
 int /*<<< orphan*/  page_counter_charge (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ page_counter_read (int /*<<< orphan*/ *) ; 
 scalar_t__ page_counter_try_charge (int /*<<< orphan*/ *,unsigned int,struct page_counter**) ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned int) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 int /*<<< orphan*/  refill_stock (struct mem_cgroup*,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_notify_resume (TYPE_1__*) ; 
 int should_force_charge () ; 
 int task_in_memcg_oom (TYPE_1__*) ; 
 unsigned long try_to_free_mem_cgroup_pages (struct mem_cgroup*,unsigned int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int try_charge(struct mem_cgroup *memcg, gfp_t gfp_mask,
		      unsigned int nr_pages)
{
	unsigned int batch = max(MEMCG_CHARGE_BATCH, nr_pages);
	int nr_retries = MEM_CGROUP_RECLAIM_RETRIES;
	struct mem_cgroup *mem_over_limit;
	struct page_counter *counter;
	unsigned long nr_reclaimed;
	bool may_swap = true;
	bool drained = false;
	enum oom_status oom_status;

	if (mem_cgroup_is_root(memcg))
		return 0;
retry:
	if (consume_stock(memcg, nr_pages))
		return 0;

	if (!do_memsw_account() ||
	    page_counter_try_charge(&memcg->memsw, batch, &counter)) {
		if (page_counter_try_charge(&memcg->memory, batch, &counter))
			goto done_restock;
		if (do_memsw_account())
			page_counter_uncharge(&memcg->memsw, batch);
		mem_over_limit = mem_cgroup_from_counter(counter, memory);
	} else {
		mem_over_limit = mem_cgroup_from_counter(counter, memsw);
		may_swap = false;
	}

	if (batch > nr_pages) {
		batch = nr_pages;
		goto retry;
	}

	/*
	 * Memcg doesn't have a dedicated reserve for atomic
	 * allocations. But like the global atomic pool, we need to
	 * put the burden of reclaim on regular allocation requests
	 * and let these go through as privileged allocations.
	 */
	if (gfp_mask & __GFP_ATOMIC)
		goto force;

	/*
	 * Unlike in global OOM situations, memcg is not in a physical
	 * memory shortage.  Allow dying and OOM-killed tasks to
	 * bypass the last charges so that they can exit quickly and
	 * free their memory.
	 */
	if (unlikely(should_force_charge()))
		goto force;

	/*
	 * Prevent unbounded recursion when reclaim operations need to
	 * allocate memory. This might exceed the limits temporarily,
	 * but we prefer facilitating memory reclaim and getting back
	 * under the limit over triggering OOM kills in these cases.
	 */
	if (unlikely(current->flags & PF_MEMALLOC))
		goto force;

	if (unlikely(task_in_memcg_oom(current)))
		goto nomem;

	if (!gfpflags_allow_blocking(gfp_mask))
		goto nomem;

	memcg_memory_event(mem_over_limit, MEMCG_MAX);

	nr_reclaimed = try_to_free_mem_cgroup_pages(mem_over_limit, nr_pages,
						    gfp_mask, may_swap);

	if (mem_cgroup_margin(mem_over_limit) >= nr_pages)
		goto retry;

	if (!drained) {
		drain_all_stock(mem_over_limit);
		drained = true;
		goto retry;
	}

	if (gfp_mask & __GFP_NORETRY)
		goto nomem;
	/*
	 * Even though the limit is exceeded at this point, reclaim
	 * may have been able to free some pages.  Retry the charge
	 * before killing the task.
	 *
	 * Only for regular pages, though: huge pages are rather
	 * unlikely to succeed so close to the limit, and we fall back
	 * to regular pages anyway in case of failure.
	 */
	if (nr_reclaimed && nr_pages <= (1 << PAGE_ALLOC_COSTLY_ORDER))
		goto retry;
	/*
	 * At task move, charge accounts can be doubly counted. So, it's
	 * better to wait until the end of task_move if something is going on.
	 */
	if (mem_cgroup_wait_acct_move(mem_over_limit))
		goto retry;

	if (nr_retries--)
		goto retry;

	if (gfp_mask & __GFP_RETRY_MAYFAIL)
		goto nomem;

	if (gfp_mask & __GFP_NOFAIL)
		goto force;

	if (fatal_signal_pending(current))
		goto force;

	/*
	 * keep retrying as long as the memcg oom killer is able to make
	 * a forward progress or bypass the charge if the oom killer
	 * couldn't make any progress.
	 */
	oom_status = mem_cgroup_oom(mem_over_limit, gfp_mask,
		       get_order(nr_pages * PAGE_SIZE));
	switch (oom_status) {
	case OOM_SUCCESS:
		nr_retries = MEM_CGROUP_RECLAIM_RETRIES;
		goto retry;
	case OOM_FAILED:
		goto force;
	default:
		goto nomem;
	}
nomem:
	if (!(gfp_mask & __GFP_NOFAIL))
		return -ENOMEM;
force:
	/*
	 * The allocation either can't fail or will lead to more memory
	 * being freed very soon.  Allow memory usage go over the limit
	 * temporarily by force charging it.
	 */
	page_counter_charge(&memcg->memory, nr_pages);
	if (do_memsw_account())
		page_counter_charge(&memcg->memsw, nr_pages);
	css_get_many(&memcg->css, nr_pages);

	return 0;

done_restock:
	css_get_many(&memcg->css, batch);
	if (batch > nr_pages)
		refill_stock(memcg, batch - nr_pages);

	/*
	 * If the hierarchy is above the normal consumption range, schedule
	 * reclaim on returning to userland.  We can perform reclaim here
	 * if __GFP_RECLAIM but let's always punt for simplicity and so that
	 * GFP_KERNEL can consistently be used during reclaim.  @memcg is
	 * not recorded as it most likely matches current's and won't
	 * change in the meantime.  As high limit is checked again before
	 * reclaim, the cost of mismatch is negligible.
	 */
	do {
		if (page_counter_read(&memcg->memory) > memcg->high) {
			/* Don't bother a random interrupted task */
			if (in_interrupt()) {
				schedule_work(&memcg->high_work);
				break;
			}
			current->memcg_nr_pages_over_high += batch;
			set_notify_resume(current);
			break;
		}
	} while ((memcg = parent_mem_cgroup(memcg)));

	return 0;
}