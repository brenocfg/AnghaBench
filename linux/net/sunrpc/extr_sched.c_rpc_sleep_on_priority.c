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
struct rpc_task {scalar_t__ tk_timeout; } ;

/* Variables and functions */
 scalar_t__ RPC_PRIORITY_LOW ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __rpc_sleep_on_priority (struct rpc_wait_queue*,struct rpc_task*,int) ; 
 int /*<<< orphan*/  rpc_sleep_check_activated (struct rpc_task*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rpc_sleep_on_priority(struct rpc_wait_queue *q, struct rpc_task *task,
		int priority)
{
	if (!rpc_sleep_check_activated(task))
		return;

	WARN_ON_ONCE(task->tk_timeout != 0);
	priority -= RPC_PRIORITY_LOW;
	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority(q, task, priority);
	spin_unlock(&q->lock);
}