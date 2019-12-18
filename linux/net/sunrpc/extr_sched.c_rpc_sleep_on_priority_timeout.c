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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 scalar_t__ RPC_PRIORITY_LOW ; 
 int /*<<< orphan*/  __rpc_sleep_on_priority_timeout (struct rpc_wait_queue*,struct rpc_task*,unsigned long,int) ; 
 int /*<<< orphan*/  rpc_sleep_check_activated (struct rpc_task*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rpc_sleep_on_priority_timeout(struct rpc_wait_queue *q,
		struct rpc_task *task, unsigned long timeout, int priority)
{
	if (!rpc_sleep_check_activated(task))
		return;

	priority -= RPC_PRIORITY_LOW;
	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority_timeout(q, task, timeout, priority);
	spin_unlock(&q->lock);
}