#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {scalar_t__ tk_status; TYPE_4__* tk_rqstp; int /*<<< orphan*/  (* tk_action ) (struct rpc_task*) ;TYPE_2__* tk_client; } ;
struct TYPE_8__ {TYPE_3__* rq_xprt; } ;
struct TYPE_7__ {int /*<<< orphan*/  pending; } ;
struct TYPE_6__ {TYPE_1__* cl_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpcretrans; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int HZ ; 
 int RPC_WAS_SENT (struct rpc_task*) ; 
 int /*<<< orphan*/  call_status (struct rpc_task*) ; 
 int /*<<< orphan*/  call_transmit_status (struct rpc_task*) ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_delay (struct rpc_task*,int) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,scalar_t__) ; 
 int /*<<< orphan*/  rpc_exit_task (struct rpc_task*) ; 
 scalar_t__ rpc_reply_expected (struct rpc_task*) ; 
 scalar_t__ rpc_task_need_encode (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_wake_up_queued_task (int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_xdr_encode (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_prepare_transmit (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_transmit (struct rpc_task*) ; 

__attribute__((used)) static void
call_transmit(struct rpc_task *task)
{
	int is_retrans = RPC_WAS_SENT(task);

	dprint_status(task);

	task->tk_action = call_status;
	if (task->tk_status < 0)
		return;
	if (!xprt_prepare_transmit(task))
		return;
	task->tk_action = call_transmit_status;
	/* Encode here so that rpcsec_gss can use correct sequence number. */
	if (rpc_task_need_encode(task)) {
		rpc_xdr_encode(task);
		/* Did the encode result in an error condition? */
		if (task->tk_status != 0) {
			/* Was the error nonfatal? */
			if (task->tk_status == -EAGAIN)
				rpc_delay(task, HZ >> 4);
			else
				rpc_exit(task, task->tk_status);
			return;
		}
	}
	xprt_transmit(task);
	if (task->tk_status < 0)
		return;
	if (is_retrans)
		task->tk_client->cl_stats->rpcretrans++;
	/*
	 * On success, ensure that we call xprt_end_transmit() before sleeping
	 * in order to allow access to the socket to other RPC requests.
	 */
	call_transmit_status(task);
	if (rpc_reply_expected(task))
		return;
	task->tk_action = rpc_exit_task;
	rpc_wake_up_queued_task(&task->tk_rqstp->rq_xprt->pending, task);
}