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
struct ff_circular_queue {scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/  abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_lock (struct ff_circular_queue*) ; 
 int /*<<< orphan*/  queue_unlock (struct ff_circular_queue*) ; 
 int /*<<< orphan*/  queue_wait (struct ff_circular_queue*) ; 

void ff_circular_queue_wait_write(struct ff_circular_queue *cq)
{
	queue_lock(cq);

	while (cq->size >= cq->capacity && !cq->abort)
		queue_wait(cq);

	queue_unlock(cq);
}