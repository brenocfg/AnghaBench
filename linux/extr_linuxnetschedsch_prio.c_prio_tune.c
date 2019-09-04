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
struct tc_prio_qopt {int bands; int* priomap; } ;
struct prio_sched_data {int bands; struct Qdisc** queues; int /*<<< orphan*/  prio2band; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  backlog; } ;
struct TYPE_3__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_2__ qstats; TYPE_1__ q; int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int TCQ_PRIO_BANDS ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int TC_PRIO_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct tc_prio_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  prio_offload (struct Qdisc*,struct tc_prio_qopt*) ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qdisc_destroy (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int prio_tune(struct Qdisc *sch, struct nlattr *opt,
		     struct netlink_ext_ack *extack)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	struct Qdisc *queues[TCQ_PRIO_BANDS];
	int oldbands = q->bands, i;
	struct tc_prio_qopt *qopt;

	if (nla_len(opt) < sizeof(*qopt))
		return -EINVAL;
	qopt = nla_data(opt);

	if (qopt->bands > TCQ_PRIO_BANDS || qopt->bands < 2)
		return -EINVAL;

	for (i = 0; i <= TC_PRIO_MAX; i++) {
		if (qopt->priomap[i] >= qopt->bands)
			return -EINVAL;
	}

	/* Before commit, make sure we can allocate all new qdiscs */
	for (i = oldbands; i < qopt->bands; i++) {
		queues[i] = qdisc_create_dflt(sch->dev_queue, &pfifo_qdisc_ops,
					      TC_H_MAKE(sch->handle, i + 1),
					      extack);
		if (!queues[i]) {
			while (i > oldbands)
				qdisc_destroy(queues[--i]);
			return -ENOMEM;
		}
	}

	prio_offload(sch, qopt);
	sch_tree_lock(sch);
	q->bands = qopt->bands;
	memcpy(q->prio2band, qopt->priomap, TC_PRIO_MAX+1);

	for (i = q->bands; i < oldbands; i++) {
		struct Qdisc *child = q->queues[i];

		qdisc_tree_reduce_backlog(child, child->q.qlen,
					  child->qstats.backlog);
		qdisc_destroy(child);
	}

	for (i = oldbands; i < q->bands; i++) {
		q->queues[i] = queues[i];
		if (q->queues[i] != &noop_qdisc)
			qdisc_hash_add(q->queues[i], true);
	}

	sch_tree_unlock(sch);
	return 0;
}