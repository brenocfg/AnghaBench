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
struct list_node {struct list_node* prev; struct list_node* next; } ;
struct list_head {struct list_node n; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_debug (struct list_head*) ; 

__attribute__((used)) static inline void list_add_tail(struct list_head *h, struct list_node *n)
{
	n->next = &h->n;
	n->prev = h->n.prev;
	h->n.prev->next = n;
	h->n.prev = n;
	(void)list_debug(h);
}