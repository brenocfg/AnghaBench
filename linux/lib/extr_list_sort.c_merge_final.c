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
typedef  scalar_t__ u8 ;
struct list_head {struct list_head* prev; struct list_head* next; } ;
typedef  scalar_t__ (* cmp_func ) (void*,struct list_head*,struct list_head*) ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) __attribute__((nonnull(2,3,4,5)))
static void merge_final(void *priv, cmp_func cmp, struct list_head *head,
			struct list_head *a, struct list_head *b)
{
	struct list_head *tail = head;
	u8 count = 0;

	for (;;) {
		/* if equal, take 'a' -- important for sort stability */
		if (cmp(priv, a, b) <= 0) {
			tail->next = a;
			a->prev = tail;
			tail = a;
			a = a->next;
			if (!a)
				break;
		} else {
			tail->next = b;
			b->prev = tail;
			tail = b;
			b = b->next;
			if (!b) {
				b = a;
				break;
			}
		}
	}

	/* Finish linking remainder of list b on to tail */
	tail->next = b;
	do {
		/*
		 * If the merge is highly unbalanced (e.g. the input is
		 * already sorted), this loop may run many iterations.
		 * Continue callbacks to the client even though no
		 * element comparison is needed, so the client's cmp()
		 * routine can invoke cond_resched() periodically.
		 */
		if (unlikely(!++count))
			cmp(priv, b, b);
		b->prev = tail;
		tail = b;
		b = b->next;
	} while (b);

	/* And the final links to make a circular doubly-linked list */
	tail->next = head;
	head->prev = tail;
}