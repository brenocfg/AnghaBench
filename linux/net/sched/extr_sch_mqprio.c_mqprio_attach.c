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
struct net_device {unsigned int num_tx_queues; unsigned int real_num_tx_queues; } ;
struct mqprio_sched {struct Qdisc** qdiscs; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 struct Qdisc* dev_graft_qdisc (int /*<<< orphan*/ ,struct Qdisc*) ; 
 int /*<<< orphan*/  kfree (struct Qdisc**) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_hash_add (struct Qdisc*,int) ; 
 struct mqprio_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (struct Qdisc*) ; 

__attribute__((used)) static void mqprio_attach(struct Qdisc *sch)
{
	struct net_device *dev = qdisc_dev(sch);
	struct mqprio_sched *priv = qdisc_priv(sch);
	struct Qdisc *qdisc, *old;
	unsigned int ntx;

	/* Attach underlying qdisc */
	for (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
		qdisc = priv->qdiscs[ntx];
		old = dev_graft_qdisc(qdisc->dev_queue, qdisc);
		if (old)
			qdisc_put(old);
		if (ntx < dev->real_num_tx_queues)
			qdisc_hash_add(qdisc, false);
	}
	kfree(priv->qdiscs);
	priv->qdiscs = NULL;
}