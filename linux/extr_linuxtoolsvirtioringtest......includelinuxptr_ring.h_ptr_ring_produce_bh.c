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
struct ptr_ring {int /*<<< orphan*/  producer_lock; } ;

/* Variables and functions */
 int __ptr_ring_produce (struct ptr_ring*,void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ptr_ring_produce_bh(struct ptr_ring *r, void *ptr)
{
	int ret;

	spin_lock_bh(&r->producer_lock);
	ret = __ptr_ring_produce(r, ptr);
	spin_unlock_bh(&r->producer_lock);

	return ret;
}