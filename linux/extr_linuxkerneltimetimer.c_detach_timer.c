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
struct hlist_node {int /*<<< orphan*/  next; int /*<<< orphan*/ * pprev; } ;
struct timer_list {struct hlist_node entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_POISON2 ; 
 int /*<<< orphan*/  __hlist_del (struct hlist_node*) ; 
 int /*<<< orphan*/  debug_deactivate (struct timer_list*) ; 

__attribute__((used)) static inline void detach_timer(struct timer_list *timer, bool clear_pending)
{
	struct hlist_node *entry = &timer->entry;

	debug_deactivate(timer);

	__hlist_del(entry);
	if (clear_pending)
		entry->pprev = NULL;
	entry->next = LIST_POISON2;
}