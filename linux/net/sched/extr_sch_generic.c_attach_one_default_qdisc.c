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
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {int priv_flags; scalar_t__ type; } ;
struct Qdisc_ops {int dummy; } ;
struct Qdisc {int flags; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int IFF_NO_QUEUE ; 
 int TCQ_F_NOPARENT ; 
 int TCQ_F_ONETXQUEUE ; 
 int /*<<< orphan*/  TC_H_ROOT ; 
 struct Qdisc_ops* default_qdisc_ops ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_is_multiqueue (struct net_device*) ; 
 struct Qdisc_ops noqueue_qdisc_ops ; 
 struct Qdisc_ops pfifo_fast_ops ; 
 struct Qdisc* qdisc_create_dflt (struct netdev_queue*,struct Qdisc_ops const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void attach_one_default_qdisc(struct net_device *dev,
				     struct netdev_queue *dev_queue,
				     void *_unused)
{
	struct Qdisc *qdisc;
	const struct Qdisc_ops *ops = default_qdisc_ops;

	if (dev->priv_flags & IFF_NO_QUEUE)
		ops = &noqueue_qdisc_ops;
	else if(dev->type == ARPHRD_CAN)
		ops = &pfifo_fast_ops;

	qdisc = qdisc_create_dflt(dev_queue, ops, TC_H_ROOT, NULL);
	if (!qdisc) {
		netdev_info(dev, "activation failed\n");
		return;
	}
	if (!netif_is_multiqueue(dev))
		qdisc->flags |= TCQ_F_ONETXQUEUE | TCQ_F_NOPARENT;
	dev_queue->qdisc_sleeping = qdisc;
}