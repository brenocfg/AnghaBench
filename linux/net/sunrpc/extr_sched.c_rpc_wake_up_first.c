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
struct rpc_wait_queue {int dummy; } ;
struct rpc_task {int dummy; } ;

/* Variables and functions */
 struct rpc_task* rpc_wake_up_first_on_wq (int /*<<< orphan*/ ,struct rpc_wait_queue*,int (*) (struct rpc_task*,void*),void*) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 

struct rpc_task *rpc_wake_up_first(struct rpc_wait_queue *queue,
		bool (*func)(struct rpc_task *, void *), void *data)
{
	return rpc_wake_up_first_on_wq(rpciod_workqueue, queue, func, data);
}