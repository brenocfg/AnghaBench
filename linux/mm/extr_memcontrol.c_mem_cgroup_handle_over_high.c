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
typedef  unsigned long u64 ;
struct mem_cgroup {int /*<<< orphan*/  css; int /*<<< orphan*/  high; int /*<<< orphan*/  memory; } ;
struct TYPE_2__ {unsigned int memcg_nr_pages_over_high; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HZ ; 
 unsigned long MEMCG_CHARGE_BATCH ; 
 unsigned long MEMCG_DELAY_PRECISION_SHIFT ; 
 unsigned long MEMCG_DELAY_SCALING_SHIFT ; 
 int /*<<< orphan*/  MEMCG_MAX_HIGH_DELAY_JIFFIES ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 unsigned long div_u64 (unsigned long,unsigned long) ; 
 struct mem_cgroup* get_mem_cgroup_from_mm (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long page_counter_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psi_memstall_enter (unsigned long*) ; 
 int /*<<< orphan*/  psi_memstall_leave (unsigned long*) ; 
 int /*<<< orphan*/  reclaim_high (struct mem_cgroup*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_killable (unsigned long) ; 

void mem_cgroup_handle_over_high(void)
{
	unsigned long usage, high, clamped_high;
	unsigned long pflags;
	unsigned long penalty_jiffies, overage;
	unsigned int nr_pages = current->memcg_nr_pages_over_high;
	struct mem_cgroup *memcg;

	if (likely(!nr_pages))
		return;

	memcg = get_mem_cgroup_from_mm(current->mm);
	reclaim_high(memcg, nr_pages, GFP_KERNEL);
	current->memcg_nr_pages_over_high = 0;

	/*
	 * memory.high is breached and reclaim is unable to keep up. Throttle
	 * allocators proactively to slow down excessive growth.
	 *
	 * We use overage compared to memory.high to calculate the number of
	 * jiffies to sleep (penalty_jiffies). Ideally this value should be
	 * fairly lenient on small overages, and increasingly harsh when the
	 * memcg in question makes it clear that it has no intention of stopping
	 * its crazy behaviour, so we exponentially increase the delay based on
	 * overage amount.
	 */

	usage = page_counter_read(&memcg->memory);
	high = READ_ONCE(memcg->high);

	if (usage <= high)
		goto out;

	/*
	 * Prevent division by 0 in overage calculation by acting as if it was a
	 * threshold of 1 page
	 */
	clamped_high = max(high, 1UL);

	overage = div_u64((u64)(usage - high) << MEMCG_DELAY_PRECISION_SHIFT,
			  clamped_high);

	penalty_jiffies = ((u64)overage * overage * HZ)
		>> (MEMCG_DELAY_PRECISION_SHIFT + MEMCG_DELAY_SCALING_SHIFT);

	/*
	 * Factor in the task's own contribution to the overage, such that four
	 * N-sized allocations are throttled approximately the same as one
	 * 4N-sized allocation.
	 *
	 * MEMCG_CHARGE_BATCH pages is nominal, so work out how much smaller or
	 * larger the current charge patch is than that.
	 */
	penalty_jiffies = penalty_jiffies * nr_pages / MEMCG_CHARGE_BATCH;

	/*
	 * Clamp the max delay per usermode return so as to still keep the
	 * application moving forwards and also permit diagnostics, albeit
	 * extremely slowly.
	 */
	penalty_jiffies = min(penalty_jiffies, MEMCG_MAX_HIGH_DELAY_JIFFIES);

	/*
	 * Don't sleep if the amount of jiffies this memcg owes us is so low
	 * that it's not even worth doing, in an attempt to be nice to those who
	 * go only a small amount over their memory.high value and maybe haven't
	 * been aggressively reclaimed enough yet.
	 */
	if (penalty_jiffies <= HZ / 100)
		goto out;

	/*
	 * If we exit early, we're guaranteed to die (since
	 * schedule_timeout_killable sets TASK_KILLABLE). This means we don't
	 * need to account for any ill-begotten jiffies to pay them off later.
	 */
	psi_memstall_enter(&pflags);
	schedule_timeout_killable(penalty_jiffies);
	psi_memstall_leave(&pflags);

out:
	css_put(&memcg->css);
}