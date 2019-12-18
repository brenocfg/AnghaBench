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
 struct rpc_task* rpc_wake_up_first (struct rpc_wait_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up_next_func ; 

struct rpc_task *rpc_wake_up_next(struct rpc_wait_queue *queue)
{
	return rpc_wake_up_first(queue, rpc_wake_up_next_func, NULL);
}