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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_list_dequeue_task (struct rpc_task*) ; 

__attribute__((used)) static void __rpc_remove_wait_queue_priority(struct rpc_task *task)
{
	__rpc_list_dequeue_task(task);
}