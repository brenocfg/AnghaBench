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
struct net_device {unsigned int real_num_tx_queues; unsigned int num_tx_queues; scalar_t__ reg_state; scalar_t__ num_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 scalar_t__ NETREG_REGISTERED ; 
 scalar_t__ NETREG_UNREGISTERING ; 
 int netdev_queue_update_kobjects (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netif_reset_xps_queues_gt (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netif_setup_tc (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  qdisc_reset_all_tx_gt (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  synchronize_net () ; 

int netif_set_real_num_tx_queues(struct net_device *dev, unsigned int txq)
{
	bool disabling;
	int rc;

	disabling = txq < dev->real_num_tx_queues;

	if (txq < 1 || txq > dev->num_tx_queues)
		return -EINVAL;

	if (dev->reg_state == NETREG_REGISTERED ||
	    dev->reg_state == NETREG_UNREGISTERING) {
		ASSERT_RTNL();

		rc = netdev_queue_update_kobjects(dev, dev->real_num_tx_queues,
						  txq);
		if (rc)
			return rc;

		if (dev->num_tc)
			netif_setup_tc(dev, txq);

		dev->real_num_tx_queues = txq;

		if (disabling) {
			synchronize_net();
			qdisc_reset_all_tx_gt(dev, txq);
#ifdef CONFIG_XPS
			netif_reset_xps_queues_gt(dev, txq);
#endif
		}
	} else {
		dev->real_num_tx_queues = txq;
	}

	return 0;
}