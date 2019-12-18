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
struct TYPE_2__ {unsigned long expires; int /*<<< orphan*/  dwork; } ;
struct rpc_wait_queue {TYPE_1__ timer_list; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void
rpc_set_queue_timer(struct rpc_wait_queue *queue, unsigned long expires)
{
	unsigned long now = jiffies;
	queue->timer_list.expires = expires;
	if (time_before_eq(expires, now))
		expires = 0;
	else
		expires -= now;
	mod_delayed_work(rpciod_workqueue, &queue->timer_list.dwork, expires);
}