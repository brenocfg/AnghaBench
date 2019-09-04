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
struct ptr_ring {int /*<<< orphan*/  consumer_lock; int /*<<< orphan*/  producer_lock; scalar_t__ consumer_tail; scalar_t__ consumer_head; scalar_t__ producer; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __ptr_ring_init_queue_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ptr_ring_set_size (struct ptr_ring*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ptr_ring_init(struct ptr_ring *r, int size, gfp_t gfp)
{
	r->queue = __ptr_ring_init_queue_alloc(size, gfp);
	if (!r->queue)
		return -ENOMEM;

	__ptr_ring_set_size(r, size);
	r->producer = r->consumer_head = r->consumer_tail = 0;
	spin_lock_init(&r->producer_lock);
	spin_lock_init(&r->consumer_lock);

	return 0;
}