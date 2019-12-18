#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct deferred_split {int /*<<< orphan*/  split_queue_lock; int /*<<< orphan*/  split_queue_len; int /*<<< orphan*/  split_queue; } ;
struct TYPE_4__ {struct mem_cgroup* mem_cgroup; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  THP_DEFERRED_SPLIT_PAGE ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 TYPE_2__* compound_head (struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 TYPE_1__ deferred_split_shrinker ; 
 struct deferred_split* get_deferred_split_queue (struct page*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcg_set_shrinker_bit (struct mem_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_deferred_list (struct page*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void deferred_split_huge_page(struct page *page)
{
	struct deferred_split *ds_queue = get_deferred_split_queue(page);
#ifdef CONFIG_MEMCG
	struct mem_cgroup *memcg = compound_head(page)->mem_cgroup;
#endif
	unsigned long flags;

	VM_BUG_ON_PAGE(!PageTransHuge(page), page);

	/*
	 * The try_to_unmap() in page reclaim path might reach here too,
	 * this may cause a race condition to corrupt deferred split queue.
	 * And, if page reclaim is already handling the same page, it is
	 * unnecessary to handle it again in shrinker.
	 *
	 * Check PageSwapCache to determine if the page is being
	 * handled by page reclaim since THP swap would add the page into
	 * swap cache before calling try_to_unmap().
	 */
	if (PageSwapCache(page))
		return;

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	if (list_empty(page_deferred_list(page))) {
		count_vm_event(THP_DEFERRED_SPLIT_PAGE);
		list_add_tail(page_deferred_list(page), &ds_queue->split_queue);
		ds_queue->split_queue_len++;
#ifdef CONFIG_MEMCG
		if (memcg)
			memcg_set_shrinker_bit(memcg, page_to_nid(page),
					       deferred_split_shrinker.id);
#endif
	}
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);
}