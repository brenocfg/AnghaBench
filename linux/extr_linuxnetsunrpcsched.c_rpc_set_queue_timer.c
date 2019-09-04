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
struct TYPE_2__ {unsigned long expires; int /*<<< orphan*/  timer; } ;
struct rpc_wait_queue {TYPE_1__ timer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
rpc_set_queue_timer(struct rpc_wait_queue *queue, unsigned long expires)
{
	queue->timer_list.expires = expires;
	mod_timer(&queue->timer_list.timer, expires);
}