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
struct rpc_task {int /*<<< orphan*/  tk_calldata; TYPE_1__* tk_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_call_prepare ) (struct rpc_task*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_task*,int /*<<< orphan*/ ) ; 

void rpc_prepare_task(struct rpc_task *task)
{
	task->tk_ops->rpc_call_prepare(task, task->tk_calldata);
}