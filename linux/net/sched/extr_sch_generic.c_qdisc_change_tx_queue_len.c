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
struct net_device {int /*<<< orphan*/  tx_queue_len; } ;
struct Qdisc_ops {int (* change_tx_queue_len ) (struct Qdisc*,int /*<<< orphan*/ ) ;} ;
struct Qdisc {struct Qdisc_ops* ops; } ;

/* Variables and functions */
 int stub1 (struct Qdisc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qdisc_change_tx_queue_len(struct net_device *dev,
				     struct netdev_queue *dev_queue)
{
	struct Qdisc *qdisc = dev_queue->qdisc_sleeping;
	const struct Qdisc_ops *ops = qdisc->ops;

	if (ops->change_tx_queue_len)
		return ops->change_tx_queue_len(qdisc, dev->tx_queue_len);
	return 0;
}