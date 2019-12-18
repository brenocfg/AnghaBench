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
struct net_device {unsigned int tx_queue_len; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NETDEV_CHANGE_TX_QUEUE_LEN ; 
 int call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int dev_qdisc_change_tx_queue_len (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int notifier_to_errno (int) ; 

int dev_change_tx_queue_len(struct net_device *dev, unsigned long new_len)
{
	unsigned int orig_len = dev->tx_queue_len;
	int res;

	if (new_len != (unsigned int)new_len)
		return -ERANGE;

	if (new_len != orig_len) {
		dev->tx_queue_len = new_len;
		res = call_netdevice_notifiers(NETDEV_CHANGE_TX_QUEUE_LEN, dev);
		res = notifier_to_errno(res);
		if (res)
			goto err_rollback;
		res = dev_qdisc_change_tx_queue_len(dev);
		if (res)
			goto err_rollback;
	}

	return 0;

err_rollback:
	netdev_err(dev, "refused to change device tx_queue_len\n");
	dev->tx_queue_len = orig_len;
	return res;
}