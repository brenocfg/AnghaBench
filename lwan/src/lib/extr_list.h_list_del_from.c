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
struct list_node {struct list_node* next; } ;
struct list_head {struct list_node n; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  list_del (struct list_node*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static inline void list_del_from(struct list_head *h, struct list_node *n)
{
#ifdef _LIST_DEBUG
	{
		/* Thorough check: make sure it was in list! */
		struct list_node *i;
		for (i = h->n.next; i != n; i = i->next)
			assert(i != &h->n);
	}
#else
        (void)h;
#endif /* _LIST_DEBUG */

	/* Quick test that catches a surprising number of bugs. */
	assert(!list_empty(h));
	list_del(n);
}