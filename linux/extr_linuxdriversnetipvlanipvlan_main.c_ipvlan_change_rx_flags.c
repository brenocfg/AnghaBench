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
struct net_device {int flags; } ;
struct ipvl_dev {struct net_device* phy_dev; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ipvlan_change_rx_flags(struct net_device *dev, int change)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct net_device *phy_dev = ipvlan->phy_dev;

	if (change & IFF_ALLMULTI)
		dev_set_allmulti(phy_dev, dev->flags & IFF_ALLMULTI? 1 : -1);
}