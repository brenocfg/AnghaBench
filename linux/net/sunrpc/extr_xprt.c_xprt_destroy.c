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
struct rpc_xprt {int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  timer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_destroy_cb ; 

__attribute__((used)) static void xprt_destroy(struct rpc_xprt *xprt)
{
	dprintk("RPC:       destroying transport %p\n", xprt);

	/*
	 * Exclude transport connect/disconnect handlers and autoclose
	 */
	wait_on_bit_lock(&xprt->state, XPRT_LOCKED, TASK_UNINTERRUPTIBLE);

	del_timer_sync(&xprt->timer);

	/*
	 * Destroy sockets etc from the system workqueue so they can
	 * safely flush receive work running on rpciod.
	 */
	INIT_WORK(&xprt->task_cleanup, xprt_destroy_cb);
	schedule_work(&xprt->task_cleanup);
}