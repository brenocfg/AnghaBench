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
struct rpc_rqst {int /*<<< orphan*/  rq_pin; TYPE_1__* rq_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_MSG_PIN_WAIT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

void xprt_unpin_rqst(struct rpc_rqst *req)
{
	if (!test_bit(RPC_TASK_MSG_PIN_WAIT, &req->rq_task->tk_runstate)) {
		atomic_dec(&req->rq_pin);
		return;
	}
	if (atomic_dec_and_test(&req->rq_pin))
		wake_up_var(&req->rq_pin);
}