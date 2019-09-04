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
struct pglist_data {int /*<<< orphan*/  split_queue_lock; int /*<<< orphan*/  split_queue_len; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct pglist_data* NODE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_compound_page (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_deferred_list (struct page*) ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void free_transhuge_page(struct page *page)
{
	struct pglist_data *pgdata = NODE_DATA(page_to_nid(page));
	unsigned long flags;

	spin_lock_irqsave(&pgdata->split_queue_lock, flags);
	if (!list_empty(page_deferred_list(page))) {
		pgdata->split_queue_len--;
		list_del(page_deferred_list(page));
	}
	spin_unlock_irqrestore(&pgdata->split_queue_lock, flags);
	free_compound_page(page);
}