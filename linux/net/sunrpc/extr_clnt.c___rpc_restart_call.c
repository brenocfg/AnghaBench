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
struct rpc_task {void (* tk_action ) (struct rpc_task*) ;scalar_t__ tk_rpc_status; scalar_t__ tk_status; } ;

/* Variables and functions */

__attribute__((used)) static int
__rpc_restart_call(struct rpc_task *task, void (*action)(struct rpc_task *))
{
	task->tk_status = 0;
	task->tk_rpc_status = 0;
	task->tk_action = action;
	return 1;
}