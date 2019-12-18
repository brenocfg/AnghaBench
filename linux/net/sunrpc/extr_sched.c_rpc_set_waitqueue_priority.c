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
struct rpc_wait_queue {int priority; unsigned int nr; } ;

/* Variables and functions */

__attribute__((used)) static void rpc_set_waitqueue_priority(struct rpc_wait_queue *queue, int priority)
{
	if (queue->priority != priority) {
		queue->priority = priority;
		queue->nr = 1U << priority;
	}
}