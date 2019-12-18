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
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
struct tc_mqprio_qopt_offload {TYPE_1__ member_0; } ;
struct net_device {unsigned int num_tx_queues; TYPE_2__* netdev_ops; } ;
struct mqprio_sched {int mode; scalar_t__ hw_offload; scalar_t__* qdiscs; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_setup_tc ) (struct net_device*,int /*<<< orphan*/ ,struct tc_mqprio_qopt_offload*) ;} ;

/* Variables and functions */
#define  TC_MQPRIO_MODE_CHANNEL 129 
#define  TC_MQPRIO_MODE_DCB 128 
 int /*<<< orphan*/  TC_SETUP_QDISC_MQPRIO ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct mqprio_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,struct tc_mqprio_qopt_offload*) ; 

__attribute__((used)) static void mqprio_destroy(struct Qdisc *sch)
{
	struct net_device *dev = qdisc_dev(sch);
	struct mqprio_sched *priv = qdisc_priv(sch);
	unsigned int ntx;

	if (priv->qdiscs) {
		for (ntx = 0;
		     ntx < dev->num_tx_queues && priv->qdiscs[ntx];
		     ntx++)
			qdisc_put(priv->qdiscs[ntx]);
		kfree(priv->qdiscs);
	}

	if (priv->hw_offload && dev->netdev_ops->ndo_setup_tc) {
		struct tc_mqprio_qopt_offload mqprio = { { 0 } };

		switch (priv->mode) {
		case TC_MQPRIO_MODE_DCB:
		case TC_MQPRIO_MODE_CHANNEL:
			dev->netdev_ops->ndo_setup_tc(dev,
						      TC_SETUP_QDISC_MQPRIO,
						      &mqprio);
			break;
		default:
			return;
		}
	} else {
		netdev_set_num_tc(dev, 0);
	}
}