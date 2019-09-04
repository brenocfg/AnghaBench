#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_slots_cache {int /*<<< orphan*/  alloc_lock; scalar_t__ nr; int /*<<< orphan*/  cur; TYPE_1__* slots; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THP_SWAP ; 
 int HPAGE_PMD_NR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 scalar_t__ check_cache_active () ; 
 int /*<<< orphan*/  get_swap_pages (int,TYPE_1__*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ mem_cgroup_try_charge_swap (struct page*,TYPE_1__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_swap_page (struct page*,TYPE_1__) ; 
 struct swap_slots_cache* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ refill_swap_slots_cache (struct swap_slots_cache*) ; 
 int /*<<< orphan*/  swp_slots ; 

swp_entry_t get_swap_page(struct page *page)
{
	swp_entry_t entry, *pentry;
	struct swap_slots_cache *cache;

	entry.val = 0;

	if (PageTransHuge(page)) {
		if (IS_ENABLED(CONFIG_THP_SWAP))
			get_swap_pages(1, &entry, HPAGE_PMD_NR);
		goto out;
	}

	/*
	 * Preemption is allowed here, because we may sleep
	 * in refill_swap_slots_cache().  But it is safe, because
	 * accesses to the per-CPU data structure are protected by the
	 * mutex cache->alloc_lock.
	 *
	 * The alloc path here does not touch cache->slots_ret
	 * so cache->free_lock is not taken.
	 */
	cache = raw_cpu_ptr(&swp_slots);

	if (likely(check_cache_active() && cache->slots)) {
		mutex_lock(&cache->alloc_lock);
		if (cache->slots) {
repeat:
			if (cache->nr) {
				pentry = &cache->slots[cache->cur++];
				entry = *pentry;
				pentry->val = 0;
				cache->nr--;
			} else {
				if (refill_swap_slots_cache(cache))
					goto repeat;
			}
		}
		mutex_unlock(&cache->alloc_lock);
		if (entry.val)
			goto out;
	}

	get_swap_pages(1, &entry, 1);
out:
	if (mem_cgroup_try_charge_swap(page, entry)) {
		put_swap_page(page, entry);
		entry.val = 0;
	}
	return entry;
}