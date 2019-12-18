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
struct workqueue_struct {int dummy; } ;
struct rpc_task {int /*<<< orphan*/  tk_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_final_put_task (struct rpc_task*,struct workqueue_struct*) ; 
 int /*<<< orphan*/  rpc_release_resources_task (struct rpc_task*) ; 

__attribute__((used)) static void rpc_do_put_task(struct rpc_task *task, struct workqueue_struct *q)
{
	if (atomic_dec_and_test(&task->tk_count)) {
		rpc_release_resources_task(task);
		rpc_final_put_task(task, q);
	}
}