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
struct rpc_task {int tk_flags; scalar_t__ tk_timeouts; } ;

/* Variables and functions */
 int RPC_CALL_MAJORSEEN ; 
 int RPC_TASK_SENT ; 
 int /*<<< orphan*/  rpc_init_task_statistics (struct rpc_task*) ; 

__attribute__((used)) static void
rpc_reset_task_statistics(struct rpc_task *task)
{
	task->tk_timeouts = 0;
	task->tk_flags &= ~(RPC_CALL_MAJORSEEN|RPC_TASK_SENT);
	rpc_init_task_statistics(task);
}