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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct cbs_sched_data {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  dequeue; int /*<<< orphan*/  enqueue; scalar_t__ queue; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  cbs_list; } ;
struct Qdisc {scalar_t__ dev_queue; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int cbs_change (struct Qdisc*,struct nlattr*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  cbs_dequeue_soft ; 
 int /*<<< orphan*/  cbs_enqueue_soft ; 
 int /*<<< orphan*/  cbs_list ; 
 int /*<<< orphan*/  cbs_list_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_create_dflt (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (int /*<<< orphan*/ ,int) ; 
 struct cbs_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_init(struct Qdisc *sch, struct nlattr *opt,
		    struct netlink_ext_ack *extack)
{
	struct cbs_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);

	if (!opt) {
		NL_SET_ERR_MSG(extack, "Missing CBS qdisc options  which are mandatory");
		return -EINVAL;
	}

	q->qdisc = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
				     sch->handle, extack);
	if (!q->qdisc)
		return -ENOMEM;

	spin_lock(&cbs_list_lock);
	list_add(&q->cbs_list, &cbs_list);
	spin_unlock(&cbs_list_lock);

	qdisc_hash_add(q->qdisc, false);

	q->queue = sch->dev_queue - netdev_get_tx_queue(dev, 0);

	q->enqueue = cbs_enqueue_soft;
	q->dequeue = cbs_dequeue_soft;

	qdisc_watchdog_init(&q->watchdog, sch);

	return cbs_change(sch, opt, extack);
}