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
struct rpc_task {int tk_flags; int /*<<< orphan*/  tk_runstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_TASK_NEED_XMIT ; 
 int RPC_TASK_NO_RETRANS_TIMEOUT ; 
 int RPC_TASK_SENT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xprt_request_need_retransmit (struct rpc_task*) ; 

__attribute__((used)) static int
rpc_task_need_encode(struct rpc_task *task)
{
	return test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate) == 0 &&
		(!(task->tk_flags & RPC_TASK_SENT) ||
		 !(task->tk_flags & RPC_TASK_NO_RETRANS_TIMEOUT) ||
		 xprt_request_need_retransmit(task));
}