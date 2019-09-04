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
struct ff_circular_queue {int abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_lock (struct ff_circular_queue*) ; 
 int /*<<< orphan*/  queue_signal (struct ff_circular_queue*) ; 
 int /*<<< orphan*/  queue_unlock (struct ff_circular_queue*) ; 

void ff_circular_queue_abort(struct ff_circular_queue *cq)
{
	queue_lock(cq);
	cq->abort = true;
	queue_signal(cq);
	queue_unlock(cq);
}