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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct sighand_struct {int /*<<< orphan*/  signalfd_wqh; } ;

/* Variables and functions */
 int EPOLLHUP ; 
 int POLLFREE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int) ; 

void signalfd_cleanup(struct sighand_struct *sighand)
{
	wait_queue_head_t *wqh = &sighand->signalfd_wqh;
	/*
	 * The lockless check can race with remove_wait_queue() in progress,
	 * but in this case its caller should run under rcu_read_lock() and
	 * sighand_cachep is SLAB_TYPESAFE_BY_RCU, we can safely return.
	 */
	if (likely(!waitqueue_active(wqh)))
		return;

	/* wait_queue_entry_t->func(POLLFREE) should do remove_wait_queue() */
	wake_up_poll(wqh, EPOLLHUP | POLLFREE);
}