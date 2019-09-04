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
struct llist_node {int /*<<< orphan*/  next; } ;
struct llist_head {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 struct llist_node* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct llist_node* cmpxchg (int /*<<< orphan*/ *,struct llist_node*,struct llist_node*) ; 
 struct llist_node* smp_load_acquire (int /*<<< orphan*/ *) ; 

struct llist_node *llist_del_first(struct llist_head *head)
{
	struct llist_node *entry, *old_entry, *next;

	entry = smp_load_acquire(&head->first);
	for (;;) {
		if (entry == NULL)
			return NULL;
		old_entry = entry;
		next = READ_ONCE(entry->next);
		entry = cmpxchg(&head->first, old_entry, next);
		if (entry == old_entry)
			break;
	}

	return entry;
}