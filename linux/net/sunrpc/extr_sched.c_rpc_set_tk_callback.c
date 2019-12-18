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
struct rpc_task {int /*<<< orphan*/ * tk_callback; } ;
typedef  int /*<<< orphan*/ * rpc_action ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpc_set_tk_callback(struct rpc_task *task, rpc_action action)
{
	if (action && !WARN_ON_ONCE(task->tk_callback != NULL))
		task->tk_callback = action;
}