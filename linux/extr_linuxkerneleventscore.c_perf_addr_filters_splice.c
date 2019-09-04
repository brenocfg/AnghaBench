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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct perf_event {TYPE_1__ addr_filters; scalar_t__ parent; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_filters_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_addr_filter (struct perf_event*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_splice (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void perf_addr_filters_splice(struct perf_event *event,
				     struct list_head *head)
{
	unsigned long flags;
	LIST_HEAD(list);

	if (!has_addr_filter(event))
		return;

	/* don't bother with children, they don't have their own filters */
	if (event->parent)
		return;

	raw_spin_lock_irqsave(&event->addr_filters.lock, flags);

	list_splice_init(&event->addr_filters.list, &list);
	if (head)
		list_splice(head, &event->addr_filters.list);

	raw_spin_unlock_irqrestore(&event->addr_filters.lock, flags);

	free_filters_list(&list);
}