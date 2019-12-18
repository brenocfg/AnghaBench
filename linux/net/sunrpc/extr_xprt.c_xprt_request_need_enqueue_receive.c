#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {TYPE_1__* tk_rqstp; int /*<<< orphan*/  tk_runstate; } ;
struct rpc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq_reply_bytes_recvd; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_TASK_NEED_RECV ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
xprt_request_need_enqueue_receive(struct rpc_task *task, struct rpc_rqst *req)
{
	return !test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate) &&
		READ_ONCE(task->tk_rqstp->rq_reply_bytes_recvd) == 0;
}