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
struct net_device {int dummy; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_BRIDGE_BINDING ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int br_vlan_has_upper_bind_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  br_vlan_is_bind_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  br_vlan_set_vlan_dev_state (struct net_bridge*,struct net_device*) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void br_vlan_upper_change(struct net_device *dev,
				 struct net_device *upper_dev,
				 bool linking)
{
	struct net_bridge *br = netdev_priv(dev);

	if (!br_vlan_is_bind_vlan_dev(upper_dev))
		return;

	if (linking) {
		br_vlan_set_vlan_dev_state(br, upper_dev);
		br_opt_toggle(br, BROPT_VLAN_BRIDGE_BINDING, true);
	} else {
		br_opt_toggle(br, BROPT_VLAN_BRIDGE_BINDING,
			      br_vlan_has_upper_bind_vlan_dev(dev));
	}
}