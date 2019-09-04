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
struct rpc_rqst {TYPE_1__* rq_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_MSG_RECV ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xprt_pin_rqst(struct rpc_rqst *req)
{
	set_bit(RPC_TASK_MSG_RECV, &req->rq_task->tk_runstate);
}