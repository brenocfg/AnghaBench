#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tc_multiq_qopt {int bands; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct multiq_sched_data {int bands; int max_bands; struct Qdisc** queues; } ;
struct TYPE_6__ {int /*<<< orphan*/  backlog; } ;
struct TYPE_5__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_2__ qstats; TYPE_1__ q; int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;
struct TYPE_7__ {int real_num_tx_queues; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_is_multiqueue (TYPE_3__*) ; 
 struct tc_multiq_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 TYPE_3__* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int multiq_tune(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	struct tc_multiq_qopt *qopt;
	int i;

	if (!netif_is_multiqueue(qdisc_dev(sch)))
		return -EOPNOTSUPP;
	if (nla_len(opt) < sizeof(*qopt))
		return -EINVAL;

	qopt = nla_data(opt);

	qopt->bands = qdisc_dev(sch)->real_num_tx_queues;

	sch_tree_lock(sch);
	q->bands = qopt->bands;
	for (i = q->bands; i < q->max_bands; i++) {
		if (q->queues[i] != &noop_qdisc) {
			struct Qdisc *child = q->queues[i];
			q->queues[i] = &noop_qdisc;
			qdisc_tree_reduce_backlog(child, child->q.qlen,
						  child->qstats.backlog);
			qdisc_destroy(child);
		}
	}

	sch_tree_unlock(sch);

	for (i = 0; i < q->bands; i++) {
		if (q->queues[i] == &noop_qdisc) {
			struct Qdisc *child, *old;
			child = qdisc_create_dflt(sch->dev_queue,
						  &pfifo_qdisc_ops,
						  TC_H_MAKE(sch->handle,
							    i + 1), extack);
			if (child) {
				sch_tree_lock(sch);
				old = q->queues[i];
				q->queues[i] = child;
				if (child != &noop_qdisc)
					qdisc_hash_add(child, true);

				if (old != &noop_qdisc) {
					qdisc_tree_reduce_backlog(old,
								  old->q.qlen,
								  old->qstats.backlog);
					qdisc_destroy(old);
				}
				sch_tree_unlock(sch);
			}
		}
	}
	return 0;
}