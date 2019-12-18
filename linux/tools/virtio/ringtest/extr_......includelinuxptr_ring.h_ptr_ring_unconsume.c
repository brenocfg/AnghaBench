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
struct ptr_ring {int size; int consumer_head; int consumer_tail; int /*<<< orphan*/  consumer_lock; int /*<<< orphan*/  producer_lock; int /*<<< orphan*/ ** queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ptr_ring_unconsume(struct ptr_ring *r, void **batch, int n,
				      void (*destroy)(void *))
{
	unsigned long flags;
	int head;

	spin_lock_irqsave(&r->consumer_lock, flags);
	spin_lock(&r->producer_lock);

	if (!r->size)
		goto done;

	/*
	 * Clean out buffered entries (for simplicity). This way following code
	 * can test entries for NULL and if not assume they are valid.
	 */
	head = r->consumer_head - 1;
	while (likely(head >= r->consumer_tail))
		r->queue[head--] = NULL;
	r->consumer_tail = r->consumer_head;

	/*
	 * Go over entries in batch, start moving head back and copy entries.
	 * Stop when we run into previously unconsumed entries.
	 */
	while (n) {
		head = r->consumer_head - 1;
		if (head < 0)
			head = r->size - 1;
		if (r->queue[head]) {
			/* This batch entry will have to be destroyed. */
			goto done;
		}
		r->queue[head] = batch[--n];
		r->consumer_tail = head;
		/* matching READ_ONCE in __ptr_ring_empty for lockless tests */
		WRITE_ONCE(r->consumer_head, head);
	}

done:
	/* Destroy all entries left in the batch. */
	while (n)
		destroy(batch[--n]);
	spin_unlock(&r->producer_lock);
	spin_unlock_irqrestore(&r->consumer_lock, flags);
}