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
struct ptr_ring {int /*<<< orphan*/  consumer_lock; int /*<<< orphan*/  producer_lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 void** __ptr_ring_init_queue_alloc (int,int /*<<< orphan*/ ) ; 
 void** __ptr_ring_swap_queue (struct ptr_ring*,void**,int,int /*<<< orphan*/ ,void (*) (void*)) ; 
 int /*<<< orphan*/  kvfree (void**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int ptr_ring_resize(struct ptr_ring *r, int size, gfp_t gfp,
				  void (*destroy)(void *))
{
	unsigned long flags;
	void **queue = __ptr_ring_init_queue_alloc(size, gfp);
	void **old;

	if (!queue)
		return -ENOMEM;

	spin_lock_irqsave(&(r)->consumer_lock, flags);
	spin_lock(&(r)->producer_lock);

	old = __ptr_ring_swap_queue(r, queue, size, gfp, destroy);

	spin_unlock(&(r)->producer_lock);
	spin_unlock_irqrestore(&(r)->consumer_lock, flags);

	kvfree(old);

	return 0;
}