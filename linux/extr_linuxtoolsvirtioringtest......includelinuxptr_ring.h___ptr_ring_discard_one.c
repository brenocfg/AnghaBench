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
struct ptr_ring {int consumer_head; int consumer_tail; int batch; int size; int /*<<< orphan*/ ** queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void __ptr_ring_discard_one(struct ptr_ring *r)
{
	/* Fundamentally, what we want to do is update consumer
	 * index and zero out the entry so producer can reuse it.
	 * Doing it naively at each consume would be as simple as:
	 *       consumer = r->consumer;
	 *       r->queue[consumer++] = NULL;
	 *       if (unlikely(consumer >= r->size))
	 *               consumer = 0;
	 *       r->consumer = consumer;
	 * but that is suboptimal when the ring is full as producer is writing
	 * out new entries in the same cache line.  Defer these updates until a
	 * batch of entries has been consumed.
	 */
	/* Note: we must keep consumer_head valid at all times for __ptr_ring_empty
	 * to work correctly.
	 */
	int consumer_head = r->consumer_head;
	int head = consumer_head++;

	/* Once we have processed enough entries invalidate them in
	 * the ring all at once so producer can reuse their space in the ring.
	 * We also do this when we reach end of the ring - not mandatory
	 * but helps keep the implementation simple.
	 */
	if (unlikely(consumer_head - r->consumer_tail >= r->batch ||
		     consumer_head >= r->size)) {
		/* Zero out entries in the reverse order: this way we touch the
		 * cache line that producer might currently be reading the last;
		 * producer won't make progress and touch other cache lines
		 * besides the first one until we write out all entries.
		 */
		while (likely(head >= r->consumer_tail))
			r->queue[head--] = NULL;
		r->consumer_tail = consumer_head;
	}
	if (unlikely(consumer_head >= r->size)) {
		consumer_head = 0;
		r->consumer_tail = 0;
	}
	/* matching READ_ONCE in __ptr_ring_empty for lockless tests */
	WRITE_ONCE(r->consumer_head, consumer_head);
}