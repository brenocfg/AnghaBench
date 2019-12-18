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
struct rpc_task {int /*<<< orphan*/  tk_action; scalar_t__ tk_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_reserveresult ; 
 int /*<<< orphan*/  dprint_status (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_retry_reserve (struct rpc_task*) ; 

__attribute__((used)) static void
call_retry_reserve(struct rpc_task *task)
{
	dprint_status(task);

	task->tk_status  = 0;
	task->tk_action  = call_reserveresult;
	xprt_retry_reserve(task);
}