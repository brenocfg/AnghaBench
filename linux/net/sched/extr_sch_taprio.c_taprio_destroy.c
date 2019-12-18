#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct taprio_sched {TYPE_2__* admin_sched; TYPE_1__* oper_sched; scalar_t__* qdiscs; int /*<<< orphan*/  advance_timer; int /*<<< orphan*/  taprio_list; } ;
struct net_device {unsigned int num_tx_queues; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcu; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct taprio_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taprio_disable_offload (struct net_device*,struct taprio_sched*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taprio_free_sched_cb ; 
 int /*<<< orphan*/  taprio_list_lock ; 

__attribute__((used)) static void taprio_destroy(struct Qdisc *sch)
{
	struct taprio_sched *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	unsigned int i;

	spin_lock(&taprio_list_lock);
	list_del(&q->taprio_list);
	spin_unlock(&taprio_list_lock);

	hrtimer_cancel(&q->advance_timer);

	taprio_disable_offload(dev, q, NULL);

	if (q->qdiscs) {
		for (i = 0; i < dev->num_tx_queues && q->qdiscs[i]; i++)
			qdisc_put(q->qdiscs[i]);

		kfree(q->qdiscs);
	}
	q->qdiscs = NULL;

	netdev_set_num_tc(dev, 0);

	if (q->oper_sched)
		call_rcu(&q->oper_sched->rcu, taprio_free_sched_cb);

	if (q->admin_sched)
		call_rcu(&q->admin_sched->rcu, taprio_free_sched_cb);
}