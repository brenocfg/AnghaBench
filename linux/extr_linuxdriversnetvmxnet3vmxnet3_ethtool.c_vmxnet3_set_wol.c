#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmxnet3_adapter {int wol; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	if (wol->wolopts & (WAKE_PHY | WAKE_MCAST | WAKE_BCAST |
			    WAKE_MAGICSECURE)) {
		return -EOPNOTSUPP;
	}

	adapter->wol = wol->wolopts;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	return 0;
}