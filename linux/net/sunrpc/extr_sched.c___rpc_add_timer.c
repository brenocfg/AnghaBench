#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  expires; } ;
struct rpc_wait_queue {TYPE_3__ timer_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer_list; } ;
struct TYPE_5__ {TYPE_1__ tk_wait; } ;
struct rpc_task {unsigned long tk_timeout; TYPE_2__ u; int /*<<< orphan*/  tk_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_set_queue_timer (struct rpc_wait_queue*,unsigned long) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__rpc_add_timer(struct rpc_wait_queue *queue, struct rpc_task *task,
		unsigned long timeout)
{
	dprintk("RPC: %5u setting alarm for %u ms\n",
		task->tk_pid, jiffies_to_msecs(timeout - jiffies));

	task->tk_timeout = timeout;
	if (list_empty(&queue->timer_list.list) || time_before(timeout, queue->timer_list.expires))
		rpc_set_queue_timer(queue, timeout);
	list_add(&task->u.tk_wait.timer_list, &queue->timer_list.list);
}