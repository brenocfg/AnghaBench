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
struct rpc_task {int tk_rpc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int) ; 

__attribute__((used)) static void
__rpc_call_rpcerror(struct rpc_task *task, int tk_status, int rpc_status)
{
	task->tk_rpc_status = rpc_status;
	rpc_exit(task, tk_status);
}