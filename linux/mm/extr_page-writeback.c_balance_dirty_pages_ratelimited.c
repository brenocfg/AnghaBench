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
struct inode {int dummy; } ;
struct bdi_writeback {scalar_t__ dirty_exceeded; } ;
struct backing_dev_info {struct bdi_writeback wb; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {int nr_dirtied_pause; int nr_dirtied; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  balance_dirty_pages (struct bdi_writeback*,int) ; 
 int /*<<< orphan*/  bdi_cap_account_dirty (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdp_ratelimits ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dirty_throttle_leaks ; 
 scalar_t__ inode_cgwb_enabled (struct inode*) ; 
 struct backing_dev_info* inode_to_bdi (struct inode*) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int ratelimit_pages ; 
 int* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct bdi_writeback* wb_get_create_current (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_put (struct bdi_writeback*) ; 

void balance_dirty_pages_ratelimited(struct address_space *mapping)
{
	struct inode *inode = mapping->host;
	struct backing_dev_info *bdi = inode_to_bdi(inode);
	struct bdi_writeback *wb = NULL;
	int ratelimit;
	int *p;

	if (!bdi_cap_account_dirty(bdi))
		return;

	if (inode_cgwb_enabled(inode))
		wb = wb_get_create_current(bdi, GFP_KERNEL);
	if (!wb)
		wb = &bdi->wb;

	ratelimit = current->nr_dirtied_pause;
	if (wb->dirty_exceeded)
		ratelimit = min(ratelimit, 32 >> (PAGE_SHIFT - 10));

	preempt_disable();
	/*
	 * This prevents one CPU to accumulate too many dirtied pages without
	 * calling into balance_dirty_pages(), which can happen when there are
	 * 1000+ tasks, all of them start dirtying pages at exactly the same
	 * time, hence all honoured too large initial task->nr_dirtied_pause.
	 */
	p =  this_cpu_ptr(&bdp_ratelimits);
	if (unlikely(current->nr_dirtied >= ratelimit))
		*p = 0;
	else if (unlikely(*p >= ratelimit_pages)) {
		*p = 0;
		ratelimit = 0;
	}
	/*
	 * Pick up the dirtied pages by the exited tasks. This avoids lots of
	 * short-lived tasks (eg. gcc invocations in a kernel build) escaping
	 * the dirty throttling and livelock other long-run dirtiers.
	 */
	p = this_cpu_ptr(&dirty_throttle_leaks);
	if (*p > 0 && current->nr_dirtied < ratelimit) {
		unsigned long nr_pages_dirtied;
		nr_pages_dirtied = min(*p, ratelimit - current->nr_dirtied);
		*p -= nr_pages_dirtied;
		current->nr_dirtied += nr_pages_dirtied;
	}
	preempt_enable();

	if (unlikely(current->nr_dirtied >= ratelimit))
		balance_dirty_pages(wb, current->nr_dirtied);

	wb_put(wb);
}