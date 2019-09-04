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
struct ptr_ring {size_t consumer_head; int /*<<< orphan*/ * queue; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *__ptr_ring_peek(struct ptr_ring *r)
{
	if (likely(r->size))
		return READ_ONCE(r->queue[r->consumer_head]);
	return NULL;
}