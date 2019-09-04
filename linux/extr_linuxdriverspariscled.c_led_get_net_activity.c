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

/* Variables and functions */

__attribute__((used)) static __inline__ int led_get_net_activity(void)
{ 
#ifndef CONFIG_NET
	return 0;
#else
	static u64 rx_total_last, tx_total_last;
	u64 rx_total, tx_total;
	struct net_device *dev;
	int retval;

	rx_total = tx_total = 0;
	
	/* we are running as a workqueue task, so we can use an RCU lookup */
	rcu_read_lock();
	for_each_netdev_rcu(&init_net, dev) {
	    const struct rtnl_link_stats64 *stats;
	    struct rtnl_link_stats64 temp;
	    struct in_device *in_dev = __in_dev_get_rcu(dev);
	    if (!in_dev || !in_dev->ifa_list)
		continue;
	    if (ipv4_is_loopback(in_dev->ifa_list->ifa_local))
		continue;
	    stats = dev_get_stats(dev, &temp);
	    rx_total += stats->rx_packets;
	    tx_total += stats->tx_packets;
	}
	rcu_read_unlock();

	retval = 0;

	if (rx_total != rx_total_last) {
		rx_total_last = rx_total;
		retval |= LED_LAN_RCV;
	}

	if (tx_total != tx_total_last) {
		tx_total_last = tx_total;
		retval |= LED_LAN_TX;
	}

	return retval;
#endif
}