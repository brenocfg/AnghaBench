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
struct list_head {struct list_head* prev; struct list_head* next; } ;

/* Variables and functions */
 struct list_head* cmpxchg (struct list_head**,struct list_head*,struct list_head*) ; 
 struct list_head* xchg (struct list_head**,struct list_head*) ; 

__attribute__((used)) static inline bool list_add_tail_lockless(struct list_head *new,
					  struct list_head *head)
{
	struct list_head *prev;

	/*
	 * This is simple 'new->next = head' operation, but cmpxchg()
	 * is used in order to detect that same element has been just
	 * added to the list from another CPU: the winner observes
	 * new->next == new.
	 */
	if (cmpxchg(&new->next, new, head) != new)
		return false;

	/*
	 * Initially ->next of a new element must be updated with the head
	 * (we are inserting to the tail) and only then pointers are atomically
	 * exchanged.  XCHG guarantees memory ordering, thus ->next should be
	 * updated before pointers are actually swapped and pointers are
	 * swapped before prev->next is updated.
	 */

	prev = xchg(&head->prev, new);

	/*
	 * It is safe to modify prev->next and new->prev, because a new element
	 * is added only to the tail and new->next is updated before XCHG.
	 */

	prev->next = new;
	new->prev = prev;

	return true;
}