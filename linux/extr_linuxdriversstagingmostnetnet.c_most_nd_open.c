#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  ch_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  ch_id; } ;
struct net_dev_context {TYPE_2__ tx; TYPE_3__* iface; TYPE_1__ rx; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* request_netinfo ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  comp ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ most_start_channel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_stop_channel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct net_dev_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  on_netinfo ; 
 int /*<<< orphan*/  probe_disc_mt ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int most_nd_open(struct net_device *dev)
{
	struct net_dev_context *nd = netdev_priv(dev);
	int ret = 0;

	mutex_lock(&probe_disc_mt);

	if (most_start_channel(nd->iface, nd->rx.ch_id, &comp)) {
		netdev_err(dev, "most_start_channel() failed\n");
		ret = -EBUSY;
		goto unlock;
	}

	if (most_start_channel(nd->iface, nd->tx.ch_id, &comp)) {
		netdev_err(dev, "most_start_channel() failed\n");
		most_stop_channel(nd->iface, nd->rx.ch_id, &comp);
		ret = -EBUSY;
		goto unlock;
	}

	netif_carrier_off(dev);
	if (is_valid_ether_addr(dev->dev_addr))
		netif_dormant_off(dev);
	else
		netif_dormant_on(dev);
	netif_wake_queue(dev);
	if (nd->iface->request_netinfo)
		nd->iface->request_netinfo(nd->iface, nd->tx.ch_id, on_netinfo);

unlock:
	mutex_unlock(&probe_disc_mt);
	return ret;
}