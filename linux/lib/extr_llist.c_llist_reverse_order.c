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

/* Variables and functions */

struct llist_node *llist_reverse_order(struct llist_node *head)
{
	struct llist_node *new_head = NULL;

	while (head) {
		struct llist_node *tmp = head;
		head = head->next;
		tmp->next = new_head;
		new_head = tmp;
	}

	return new_head;
}