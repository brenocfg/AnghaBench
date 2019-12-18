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
struct netdev_lag_upper_info {int /*<<< orphan*/  tx_type; } ;
struct net_device {scalar_t__ type; int priv_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  perm_addr; } ;
struct failover_ops {int /*<<< orphan*/  (* slave_register ) (struct net_device*,struct net_device*) ;int /*<<< orphan*/  slave_handle_frame; scalar_t__ (* slave_pre_register ) (struct net_device*,struct net_device*) ;} ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int IFF_FAILOVER_SLAVE ; 
 int IFF_LIVE_RENAME_OK ; 
 int /*<<< orphan*/  NETDEV_LAG_TX_TYPE_ACTIVEBACKUP ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct net_device* failover_get_bymac (int /*<<< orphan*/ ,struct failover_ops**) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,...) ; 
 int netdev_master_upper_dev_link (struct net_device*,struct net_device*,int /*<<< orphan*/ *,struct netdev_lag_upper_info*,int /*<<< orphan*/ *) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 scalar_t__ stub1 (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int failover_slave_register(struct net_device *slave_dev)
{
	struct netdev_lag_upper_info lag_upper_info;
	struct net_device *failover_dev;
	struct failover_ops *fops;
	int err;

	if (slave_dev->type != ARPHRD_ETHER)
		goto done;

	ASSERT_RTNL();

	failover_dev = failover_get_bymac(slave_dev->perm_addr, &fops);
	if (!failover_dev)
		goto done;

	if (fops && fops->slave_pre_register &&
	    fops->slave_pre_register(slave_dev, failover_dev))
		goto done;

	err = netdev_rx_handler_register(slave_dev, fops->slave_handle_frame,
					 failover_dev);
	if (err) {
		netdev_err(slave_dev, "can not register failover rx handler (err = %d)\n",
			   err);
		goto done;
	}

	lag_upper_info.tx_type = NETDEV_LAG_TX_TYPE_ACTIVEBACKUP;
	err = netdev_master_upper_dev_link(slave_dev, failover_dev, NULL,
					   &lag_upper_info, NULL);
	if (err) {
		netdev_err(slave_dev, "can not set failover device %s (err = %d)\n",
			   failover_dev->name, err);
		goto err_upper_link;
	}

	slave_dev->priv_flags |= (IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);

	if (fops && fops->slave_register &&
	    !fops->slave_register(slave_dev, failover_dev))
		return NOTIFY_OK;

	netdev_upper_dev_unlink(slave_dev, failover_dev);
	slave_dev->priv_flags &= ~(IFF_FAILOVER_SLAVE | IFF_LIVE_RENAME_OK);
err_upper_link:
	netdev_rx_handler_unregister(slave_dev);
done:
	return NOTIFY_DONE;
}