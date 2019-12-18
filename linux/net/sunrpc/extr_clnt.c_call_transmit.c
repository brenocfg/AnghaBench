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
struct rpc_task {scalar_t__ tk_status; int /*<<< orphan*/  tk_xprt; int /*<<< orphan*/  tk_runstate; int /*<<< orphan*/  tk_action; } ;

/* Variables and functions */
 scalar_t__ ENOTCONN ; 
 int /*<<< orphan*/  RPC_TASK_NEED_XMIT ; 
 int /*<<< orphan*/  call_transmit_status ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_task_handle_transmitted (struct rpc_task*) ; 
 scalar_t__ rpc_task_transmitted (struct rpc_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_connected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprt_end_transmit (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_prepare_transmit (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_transmit (struct rpc_task*) ; 

__attribute__((used)) static void
call_transmit(struct rpc_task *task)
{
	if (rpc_task_transmitted(task)) {
		rpc_task_handle_transmitted(task);
		return;
	}

	dprint_status(task);

	task->tk_action = call_transmit_status;
	if (!xprt_prepare_transmit(task))
		return;
	task->tk_status = 0;
	if (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate)) {
		if (!xprt_connected(task->tk_xprt)) {
			task->tk_status = -ENOTCONN;
			return;
		}
		xprt_transmit(task);
	}
	xprt_end_transmit(task);
}