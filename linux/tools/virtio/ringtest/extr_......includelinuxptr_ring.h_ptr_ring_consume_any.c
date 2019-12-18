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
struct ptr_ring {int /*<<< orphan*/  consumer_lock; } ;

/* Variables and functions */
 void* __ptr_ring_consume (struct ptr_ring*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void *ptr_ring_consume_any(struct ptr_ring *r)
{
	unsigned long flags;
	void *ptr;

	spin_lock_irqsave(&r->consumer_lock, flags);
	ptr = __ptr_ring_consume(r);
	spin_unlock_irqrestore(&r->consumer_lock, flags);

	return ptr;
}