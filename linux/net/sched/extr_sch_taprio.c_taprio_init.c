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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct taprio_sched {int clockid; struct Qdisc** qdiscs; int /*<<< orphan*/  taprio_list; struct Qdisc* root; int /*<<< orphan*/  peek; int /*<<< orphan*/  dequeue; TYPE_1__ advance_timer; int /*<<< orphan*/  current_entry_lock; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int num_tx_queues; int real_num_tx_queues; } ;
struct Qdisc {scalar_t__ parent; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_TAI ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_H_MIN (int) ; 
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  advance_sched ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Qdisc** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_is_multiqueue (struct net_device*) ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (struct netdev_queue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct taprio_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int taprio_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  taprio_dequeue_soft ; 
 int /*<<< orphan*/  taprio_list ; 
 int /*<<< orphan*/  taprio_list_lock ; 
 int /*<<< orphan*/  taprio_peek_soft ; 

__attribute__((used)) static int taprio_init(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct taprio_sched *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	int i;

	spin_lock_init(&q->current_entry_lock);

	hrtimer_init(&q->advance_timer, CLOCK_TAI, HRTIMER_MODE_ABS);
	q->advance_timer.function = advance_sched;

	q->dequeue = taprio_dequeue_soft;
	q->peek = taprio_peek_soft;

	q->root = sch;

	/* We only support static clockids. Use an invalid value as default
	 * and get the valid one on taprio_change().
	 */
	q->clockid = -1;

	spin_lock(&taprio_list_lock);
	list_add(&q->taprio_list, &taprio_list);
	spin_unlock(&taprio_list_lock);

	if (sch->parent != TC_H_ROOT)
		return -EOPNOTSUPP;

	if (!netif_is_multiqueue(dev))
		return -EOPNOTSUPP;

	/* pre-allocate qdisc, attachment can't fail */
	q->qdiscs = kcalloc(dev->num_tx_queues,
			    sizeof(q->qdiscs[0]),
			    GFP_KERNEL);

	if (!q->qdiscs)
		return -ENOMEM;

	if (!opt)
		return -EINVAL;

	for (i = 0; i < dev->num_tx_queues; i++) {
		struct netdev_queue *dev_queue;
		struct Qdisc *qdisc;

		dev_queue = netdev_get_tx_queue(dev, i);
		qdisc = qdisc_create_dflt(dev_queue,
					  &pfifo_qdisc_ops,
					  TC_H_MAKE(TC_H_MAJ(sch->handle),
						    TC_H_MIN(i + 1)),
					  extack);
		if (!qdisc)
			return -ENOMEM;

		if (i < dev->real_num_tx_queues)
			qdisc_hash_add(qdisc, false);

		q->qdiscs[i] = qdisc;
	}

	return taprio_change(sch, opt, extack);
}