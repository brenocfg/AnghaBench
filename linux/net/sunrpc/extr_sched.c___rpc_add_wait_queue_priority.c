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
struct rpc_wait_queue {unsigned char maxpriority; int /*<<< orphan*/ * tasks; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_list_enqueue_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __rpc_add_wait_queue_priority(struct rpc_wait_queue *queue,
		struct rpc_task *task,
		unsigned char queue_priority)
{
	if (unlikely(queue_priority > queue->maxpriority))
		queue_priority = queue->maxpriority;
	__rpc_list_enqueue_task(&queue->tasks[queue_priority], task);
}