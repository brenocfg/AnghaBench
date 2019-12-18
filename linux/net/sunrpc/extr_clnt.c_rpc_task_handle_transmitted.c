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
struct rpc_task {int /*<<< orphan*/  tk_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_transmit_status ; 
 int /*<<< orphan*/  xprt_end_transmit (struct rpc_task*) ; 

__attribute__((used)) static void
rpc_task_handle_transmitted(struct rpc_task *task)
{
	xprt_end_transmit(task);
	task->tk_action = call_transmit_status;
}