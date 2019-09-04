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
struct ptr_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ptr_ring_discard_one (struct ptr_ring*) ; 
 void* __ptr_ring_peek (struct ptr_ring*) ; 

__attribute__((used)) static inline void *__ptr_ring_consume(struct ptr_ring *r)
{
	void *ptr;

	/* The READ_ONCE in __ptr_ring_peek guarantees that anyone
	 * accessing data through the pointer is up to date. Pairs
	 * with smp_wmb in __ptr_ring_produce.
	 */
	ptr = __ptr_ring_peek(r);
	if (ptr)
		__ptr_ring_discard_one(r);

	return ptr;
}