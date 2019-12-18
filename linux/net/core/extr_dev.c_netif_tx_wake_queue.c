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
struct netdev_queue {int /*<<< orphan*/  qdisc; int /*<<< orphan*/  state; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QUEUE_STATE_DRV_XOFF ; 
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 struct Qdisc* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void netif_tx_wake_queue(struct netdev_queue *dev_queue)
{
	if (test_and_clear_bit(__QUEUE_STATE_DRV_XOFF, &dev_queue->state)) {
		struct Qdisc *q;

		rcu_read_lock();
		q = rcu_dereference(dev_queue->qdisc);
		__netif_schedule(q);
		rcu_read_unlock();
	}
}