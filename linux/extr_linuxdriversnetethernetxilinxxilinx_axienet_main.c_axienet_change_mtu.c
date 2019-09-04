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
struct axienet_local {scalar_t__ rxmem; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 scalar_t__ XAE_TRL_SIZE ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int axienet_change_mtu(struct net_device *ndev, int new_mtu)
{
	struct axienet_local *lp = netdev_priv(ndev);

	if (netif_running(ndev))
		return -EBUSY;

	if ((new_mtu + VLAN_ETH_HLEN +
		XAE_TRL_SIZE) > lp->rxmem)
		return -EINVAL;

	ndev->mtu = new_mtu;

	return 0;
}