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
 int /*<<< orphan*/  kfree (void***) ; 
 void*** kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int ptr_ring_resize_multiple(struct ptr_ring **rings,
					   unsigned int nrings,
					   int size,
					   gfp_t gfp, void (*destroy)(void *))
{
	unsigned long flags;
	void ***queues;
	int i;

	queues = kmalloc_array(nrings, sizeof(*queues), gfp);
	if (!queues)
		goto noqueues;

	for (i = 0; i < nrings; ++i) {
		queues[i] = __ptr_ring_init_queue_alloc(size, gfp);
		if (!queues[i])
			goto nomem;
	}

	for (i = 0; i < nrings; ++i) {
		spin_lock_irqsave(&(rings[i])->consumer_lock, flags);
		spin_lock(&(rings[i])->producer_lock);
		queues[i] = __ptr_ring_swap_queue(rings[i], queues[i],
						  size, gfp, destroy);
		spin_unlock(&(rings[i])->producer_lock);
		spin_unlock_irqrestore(&(rings[i])->consumer_lock, flags);
	}

	for (i = 0; i < nrings; ++i)
		kvfree(queues[i]);

	kfree(queues);

	return 0;

nomem:
	while (--i >= 0)
		kvfree(queues[i]);

	kfree(queues);

noqueues:
	return -ENOMEM;
}