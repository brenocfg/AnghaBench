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
struct eppoll_entry {int /*<<< orphan*/  wait; int /*<<< orphan*/  whead; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smp_load_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep_remove_wait_queue(struct eppoll_entry *pwq)
{
	wait_queue_head_t *whead;

	rcu_read_lock();
	/*
	 * If it is cleared by POLLFREE, it should be rcu-safe.
	 * If we read NULL we need a barrier paired with
	 * smp_store_release() in ep_poll_callback(), otherwise
	 * we rely on whead->lock.
	 */
	whead = smp_load_acquire(&pwq->whead);
	if (whead)
		remove_wait_queue(whead, &pwq->wait);
	rcu_read_unlock();
}