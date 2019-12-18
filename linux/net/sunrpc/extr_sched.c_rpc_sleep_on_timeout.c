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
struct rpc_wait_queue {int /*<<< orphan*/  lock; } ;
struct rpc_task {int /*<<< orphan*/  tk_priority; } ;
typedef  int /*<<< orphan*/  rpc_action ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_sleep_on_priority_timeout (struct rpc_wait_queue*,struct rpc_task*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_set_tk_callback (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sleep_check_activated (struct rpc_task*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rpc_sleep_on_timeout(struct rpc_wait_queue *q, struct rpc_task *task,
				rpc_action action, unsigned long timeout)
{
	if (!rpc_sleep_check_activated(task))
		return;

	rpc_set_tk_callback(task, action);

	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority_timeout(q, task, timeout, task->tk_priority);
	spin_unlock(&q->lock);
}