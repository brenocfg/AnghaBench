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
struct net_device {int mtu; } ;
struct emac_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int emac_reinit_locked (struct emac_adapter*) ; 
 int /*<<< orphan*/  hw ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct emac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int emac_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	netif_info(adpt, hw, adpt->netdev,
		   "changing MTU from %d to %d\n", netdev->mtu,
		   new_mtu);
	netdev->mtu = new_mtu;

	if (netif_running(netdev))
		return emac_reinit_locked(adpt);

	return 0;
}