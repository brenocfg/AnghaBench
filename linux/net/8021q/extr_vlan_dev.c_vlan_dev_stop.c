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
struct vlan_dev_priv {int flags; struct net_device* real_dev; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int VLAN_FLAG_BRIDGE_BINDING ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static int vlan_dev_stop(struct net_device *dev)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	struct net_device *real_dev = vlan->real_dev;

	dev_mc_unsync(real_dev, dev);
	dev_uc_unsync(real_dev, dev);
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
	if (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(real_dev, -1);

	if (!ether_addr_equal(dev->dev_addr, real_dev->dev_addr))
		dev_uc_del(real_dev, dev->dev_addr);

	if (!(vlan->flags & VLAN_FLAG_BRIDGE_BINDING))
		netif_carrier_off(dev);
	return 0;
}