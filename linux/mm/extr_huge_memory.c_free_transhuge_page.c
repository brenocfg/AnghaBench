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
struct page {int dummy; } ;
struct deferred_split {int /*<<< orphan*/  split_queue_lock; int /*<<< orphan*/  split_queue_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_compound_page (struct page*) ; 
 struct deferred_split* get_deferred_split_queue (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_deferred_list (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void free_transhuge_page(struct page *page)
{
	struct deferred_split *ds_queue = get_deferred_split_queue(page);
	unsigned long flags;

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	if (!list_empty(page_deferred_list(page))) {
		ds_queue->split_queue_len--;
		list_del(page_deferred_list(page));
	}
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);
	free_compound_page(page);
}