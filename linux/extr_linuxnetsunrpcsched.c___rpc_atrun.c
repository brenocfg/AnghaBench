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
struct rpc_task {int /*<<< orphan*/  tk_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 

__attribute__((used)) static void __rpc_atrun(struct rpc_task *task)
{
	if (task->tk_status == -ETIMEDOUT)
		task->tk_status = 0;
}