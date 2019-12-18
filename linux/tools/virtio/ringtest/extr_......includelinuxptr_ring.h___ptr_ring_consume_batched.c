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
 void* __ptr_ring_consume (struct ptr_ring*) ; 

__attribute__((used)) static inline int __ptr_ring_consume_batched(struct ptr_ring *r,
					     void **array, int n)
{
	void *ptr;
	int i;

	for (i = 0; i < n; i++) {
		ptr = __ptr_ring_consume(r);
		if (!ptr)
			break;
		array[i] = ptr;
	}

	return i;
}