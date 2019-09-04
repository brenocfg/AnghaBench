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
struct vlan_dev_priv {int /*<<< orphan*/  nr_egress_mappings; int /*<<< orphan*/  nr_ingress_mappings; } ;
struct net_device {int dummy; } ;
struct ifla_vlan_flags {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device const*) ; 
 size_t vlan_qos_map_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t vlan_get_size(const struct net_device *dev)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);

	return nla_total_size(2) +	/* IFLA_VLAN_PROTOCOL */
	       nla_total_size(2) +	/* IFLA_VLAN_ID */
	       nla_total_size(sizeof(struct ifla_vlan_flags)) + /* IFLA_VLAN_FLAGS */
	       vlan_qos_map_size(vlan->nr_ingress_mappings) +
	       vlan_qos_map_size(vlan->nr_egress_mappings);
}