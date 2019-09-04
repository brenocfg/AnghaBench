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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ipvl_dev {struct net_device* phy_dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 int vlan_vid_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_vlan_rx_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct net_device *phy_dev = ipvlan->phy_dev;

	return vlan_vid_add(phy_dev, proto, vid);
}