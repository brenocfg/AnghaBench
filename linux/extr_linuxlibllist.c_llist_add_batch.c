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
struct llist_node {struct llist_node* next; } ;
struct llist_head {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 struct llist_node* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct llist_node* cmpxchg (int /*<<< orphan*/ *,struct llist_node*,struct llist_node*) ; 

bool llist_add_batch(struct llist_node *new_first, struct llist_node *new_last,
		     struct llist_head *head)
{
	struct llist_node *first;

	do {
		new_last->next = first = READ_ONCE(head->first);
	} while (cmpxchg(&head->first, first, new_first) != first);

	return !first;
}