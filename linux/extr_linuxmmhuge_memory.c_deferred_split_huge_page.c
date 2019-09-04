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
struct pglist_data {int /*<<< orphan*/  split_queue_lock; int /*<<< orphan*/  split_queue_len; int /*<<< orphan*/  split_queue; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct pglist_data* NODE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  THP_DEFERRED_SPLIT_PAGE ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_deferred_list (struct page*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void deferred_split_huge_page(struct page *page)
{
	struct pglist_data *pgdata = NODE_DATA(page_to_nid(page));
	unsigned long flags;

	VM_BUG_ON_PAGE(!PageTransHuge(page), page);

	spin_lock_irqsave(&pgdata->split_queue_lock, flags);
	if (list_empty(page_deferred_list(page))) {
		count_vm_event(THP_DEFERRED_SPLIT_PAGE);
		list_add_tail(page_deferred_list(page), &pgdata->split_queue);
		pgdata->split_queue_len++;
	}
	spin_unlock_irqrestore(&pgdata->split_queue_lock, flags);
}