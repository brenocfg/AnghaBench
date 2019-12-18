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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; scalar_t__ snd_task; int /*<<< orphan*/  pending; int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task_set_status (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprtiod_workqueue ; 

void xprt_force_disconnect(struct rpc_xprt *xprt)
{
	/* Don't race with the test_bit() in xprt_clear_locked() */
	spin_lock(&xprt->transport_lock);
	set_bit(XPRT_CLOSE_WAIT, &xprt->state);
	/* Try to schedule an autoclose RPC call */
	if (test_and_set_bit(XPRT_LOCKED, &xprt->state) == 0)
		queue_work(xprtiod_workqueue, &xprt->task_cleanup);
	else if (xprt->snd_task)
		rpc_wake_up_queued_task_set_status(&xprt->pending,
				xprt->snd_task, -ENOTCONN);
	spin_unlock(&xprt->transport_lock);
}