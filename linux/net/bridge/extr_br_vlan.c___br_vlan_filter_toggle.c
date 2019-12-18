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
struct TYPE_2__ {unsigned long vlan_filtering; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; int /*<<< orphan*/  orig_dev; } ;
struct net_bridge {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_ENABLED ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING ; 
 int /*<<< orphan*/  SWITCHDEV_F_SKIP_EOPNOTSUPP ; 
 int /*<<< orphan*/  br_manage_promisc (struct net_bridge*) ; 
 int br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_recalculate_fwd_mask (struct net_bridge*) ; 
 int /*<<< orphan*/  recalculate_group_addr (struct net_bridge*) ; 
 int switchdev_port_attr_set (int /*<<< orphan*/ ,struct switchdev_attr*) ; 

int __br_vlan_filter_toggle(struct net_bridge *br, unsigned long val)
{
	struct switchdev_attr attr = {
		.orig_dev = br->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP,
		.u.vlan_filtering = val,
	};
	int err;

	if (br_opt_get(br, BROPT_VLAN_ENABLED) == !!val)
		return 0;

	err = switchdev_port_attr_set(br->dev, &attr);
	if (err && err != -EOPNOTSUPP)
		return err;

	br_opt_toggle(br, BROPT_VLAN_ENABLED, !!val);
	br_manage_promisc(br);
	recalculate_group_addr(br);
	br_recalculate_fwd_mask(br);

	return 0;
}