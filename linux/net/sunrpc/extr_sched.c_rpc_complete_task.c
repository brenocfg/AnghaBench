#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ wait_queue_head_t ;
struct wait_bit_key {int dummy; } ;
struct rpc_task {int /*<<< orphan*/  tk_count; int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_ACTIVE ; 
 int /*<<< orphan*/  TASK_NORMAL ; 
 struct wait_bit_key __WAIT_BIT_KEY_INITIALIZER (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake_up_locked_key (TYPE_1__*,int /*<<< orphan*/ ,struct wait_bit_key*) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 TYPE_1__* bit_waitqueue (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_rpc_task_complete (struct rpc_task*,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (TYPE_1__*) ; 

__attribute__((used)) static int rpc_complete_task(struct rpc_task *task)
{
	void *m = &task->tk_runstate;
	wait_queue_head_t *wq = bit_waitqueue(m, RPC_TASK_ACTIVE);
	struct wait_bit_key k = __WAIT_BIT_KEY_INITIALIZER(m, RPC_TASK_ACTIVE);
	unsigned long flags;
	int ret;

	trace_rpc_task_complete(task, NULL);

	spin_lock_irqsave(&wq->lock, flags);
	clear_bit(RPC_TASK_ACTIVE, &task->tk_runstate);
	ret = atomic_dec_and_test(&task->tk_count);
	if (waitqueue_active(wq))
		__wake_up_locked_key(wq, TASK_NORMAL, &k);
	spin_unlock_irqrestore(&wq->lock, flags);
	return ret;
}