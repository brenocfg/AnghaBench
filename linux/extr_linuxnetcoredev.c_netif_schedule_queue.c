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
struct netdev_queue {int state; int /*<<< orphan*/  qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int QUEUE_STATE_ANY_XOFF ; 
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 struct Qdisc* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void netif_schedule_queue(struct netdev_queue *txq)
{
	rcu_read_lock();
	if (!(txq->state & QUEUE_STATE_ANY_XOFF)) {
		struct Qdisc *q = rcu_dereference(txq->qdisc);

		__netif_schedule(q);
	}
	rcu_read_unlock();
}