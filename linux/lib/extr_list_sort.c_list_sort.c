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
typedef  int /*<<< orphan*/  cmp_func ;

/* Variables and functions */
 scalar_t__ likely (size_t) ; 
 struct list_head* merge (void*,int /*<<< orphan*/ ,struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  merge_final (void*,int /*<<< orphan*/ ,struct list_head*,struct list_head*,struct list_head*) ; 

__attribute__((nonnull(2,3)))
void list_sort(void *priv, struct list_head *head,
		int (*cmp)(void *priv, struct list_head *a,
			struct list_head *b))
{
	struct list_head *list = head->next, *pending = NULL;
	size_t count = 0;	/* Count of pending */

	if (list == head->prev)	/* Zero or one elements */
		return;

	/* Convert to a null-terminated singly-linked list. */
	head->prev->next = NULL;

	/*
	 * Data structure invariants:
	 * - All lists are singly linked and null-terminated; prev
	 *   pointers are not maintained.
	 * - pending is a prev-linked "list of lists" of sorted
	 *   sublists awaiting further merging.
	 * - Each of the sorted sublists is power-of-two in size.
	 * - Sublists are sorted by size and age, smallest & newest at front.
	 * - There are zero to two sublists of each size.
	 * - A pair of pending sublists are merged as soon as the number
	 *   of following pending elements equals their size (i.e.
	 *   each time count reaches an odd multiple of that size).
	 *   That ensures each later final merge will be at worst 2:1.
	 * - Each round consists of:
	 *   - Merging the two sublists selected by the highest bit
	 *     which flips when count is incremented, and
	 *   - Adding an element from the input as a size-1 sublist.
	 */
	do {
		size_t bits;
		struct list_head **tail = &pending;

		/* Find the least-significant clear bit in count */
		for (bits = count; bits & 1; bits >>= 1)
			tail = &(*tail)->prev;
		/* Do the indicated merge */
		if (likely(bits)) {
			struct list_head *a = *tail, *b = a->prev;

			a = merge(priv, (cmp_func)cmp, b, a);
			/* Install the merged result in place of the inputs */
			a->prev = b->prev;
			*tail = a;
		}

		/* Move one element from input list to pending */
		list->prev = pending;
		pending = list;
		list = list->next;
		pending->next = NULL;
		count++;
	} while (list);

	/* End of input; merge together all the pending lists. */
	list = pending;
	pending = pending->prev;
	for (;;) {
		struct list_head *next = pending->prev;

		if (!next)
			break;
		list = merge(priv, (cmp_func)cmp, pending, list);
		pending = next;
	}
	/* The final merge, rebuilding prev links */
	merge_final(priv, (cmp_func)cmp, head, pending, list);
}