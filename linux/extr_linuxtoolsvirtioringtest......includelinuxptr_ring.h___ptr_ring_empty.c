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
struct ptr_ring {int /*<<< orphan*/  consumer_head; int /*<<< orphan*/ * queue; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool __ptr_ring_empty(struct ptr_ring *r)
{
	if (likely(r->size))
		return !r->queue[READ_ONCE(r->consumer_head)];
	return true;
}