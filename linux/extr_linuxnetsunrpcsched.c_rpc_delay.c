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
struct rpc_task {unsigned long tk_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_atrun ; 
 int /*<<< orphan*/  delay_queue ; 
 int /*<<< orphan*/  rpc_sleep_on (int /*<<< orphan*/ *,struct rpc_task*,int /*<<< orphan*/ ) ; 

void rpc_delay(struct rpc_task *task, unsigned long delay)
{
	task->tk_timeout = delay;
	rpc_sleep_on(&delay_queue, task, __rpc_atrun);
}