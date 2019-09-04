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
struct xenvif {scalar_t__ can_sg; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 int ETH_MAX_MTU ; 
 int VLAN_ETH_HLEN ; 
 struct xenvif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int xenvif_change_mtu(struct net_device *dev, int mtu)
{
	struct xenvif *vif = netdev_priv(dev);
	int max = vif->can_sg ? ETH_MAX_MTU - VLAN_ETH_HLEN : ETH_DATA_LEN;

	if (mtu > max)
		return -EINVAL;
	dev->mtu = mtu;
	return 0;
}