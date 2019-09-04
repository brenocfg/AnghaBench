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
struct rpc_task {int tk_garb_retry; int tk_cred_retry; int tk_rebind_retry; int /*<<< orphan*/  tk_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void
rpc_init_task_statistics(struct rpc_task *task)
{
	/* Initialize retry counters */
	task->tk_garb_retry = 2;
	task->tk_cred_retry = 2;
	task->tk_rebind_retry = 2;

	/* starting timestamp */
	task->tk_start = ktime_get();
}