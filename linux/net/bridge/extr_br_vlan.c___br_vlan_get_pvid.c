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
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  br_get_pvid (struct net_bridge_vlan_group*) ; 
 struct net_bridge_vlan_group* br_vlan_group (int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* nbp_vlan_group (struct net_bridge_port*) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device const*) ; 
 scalar_t__ netif_is_bridge_master (struct net_device const*) ; 

__attribute__((used)) static int __br_vlan_get_pvid(const struct net_device *dev,
			      struct net_bridge_port *p, u16 *p_pvid)
{
	struct net_bridge_vlan_group *vg;

	if (p)
		vg = nbp_vlan_group(p);
	else if (netif_is_bridge_master(dev))
		vg = br_vlan_group(netdev_priv(dev));
	else
		return -EINVAL;

	*p_pvid = br_get_pvid(vg);
	return 0;
}