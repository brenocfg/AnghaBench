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
struct workqueue_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tk_work; } ;
struct rpc_task {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_async_release ; 
 int /*<<< orphan*/  rpc_free_task (struct rpc_task*) ; 

__attribute__((used)) static void rpc_final_put_task(struct rpc_task *task,
		struct workqueue_struct *q)
{
	if (q != NULL) {
		INIT_WORK(&task->u.tk_work, rpc_async_release);
		queue_work(q, &task->u.tk_work);
	} else
		rpc_free_task(task);
}