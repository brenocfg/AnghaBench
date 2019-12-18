#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vlan_filtering; } ;
struct switchdev_attr {TYPE_1__ u; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; int /*<<< orphan*/  orig_dev; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_bridge_vlan_group {int /*<<< orphan*/  vlan_hash; int /*<<< orphan*/  vlan_list; } ;
struct net_bridge_port {int /*<<< orphan*/  vlgrp; TYPE_2__* br; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ default_pvid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int /*<<< orphan*/  BROPT_VLAN_ENABLED ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING ; 
 int /*<<< orphan*/  SWITCHDEV_F_SKIP_EOPNOTSUPP ; 
 int /*<<< orphan*/  br_opt_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_rht_params ; 
 int /*<<< orphan*/  kfree (struct net_bridge_vlan_group*) ; 
 struct net_bridge_vlan_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nbp_vlan_add (struct net_bridge_port*,scalar_t__,int,int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_bridge_vlan_group*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int switchdev_port_attr_set (int /*<<< orphan*/ ,struct switchdev_attr*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  vlan_tunnel_deinit (struct net_bridge_vlan_group*) ; 
 int vlan_tunnel_init (struct net_bridge_vlan_group*) ; 

int nbp_vlan_init(struct net_bridge_port *p, struct netlink_ext_ack *extack)
{
	struct switchdev_attr attr = {
		.orig_dev = p->br->dev,
		.id = SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING,
		.flags = SWITCHDEV_F_SKIP_EOPNOTSUPP,
		.u.vlan_filtering = br_opt_get(p->br, BROPT_VLAN_ENABLED),
	};
	struct net_bridge_vlan_group *vg;
	int ret = -ENOMEM;

	vg = kzalloc(sizeof(struct net_bridge_vlan_group), GFP_KERNEL);
	if (!vg)
		goto out;

	ret = switchdev_port_attr_set(p->dev, &attr);
	if (ret && ret != -EOPNOTSUPP)
		goto err_vlan_enabled;

	ret = rhashtable_init(&vg->vlan_hash, &br_vlan_rht_params);
	if (ret)
		goto err_rhtbl;
	ret = vlan_tunnel_init(vg);
	if (ret)
		goto err_tunnel_init;
	INIT_LIST_HEAD(&vg->vlan_list);
	rcu_assign_pointer(p->vlgrp, vg);
	if (p->br->default_pvid) {
		bool changed;

		ret = nbp_vlan_add(p, p->br->default_pvid,
				   BRIDGE_VLAN_INFO_PVID |
				   BRIDGE_VLAN_INFO_UNTAGGED,
				   &changed, extack);
		if (ret)
			goto err_vlan_add;
	}
out:
	return ret;

err_vlan_add:
	RCU_INIT_POINTER(p->vlgrp, NULL);
	synchronize_rcu();
	vlan_tunnel_deinit(vg);
err_tunnel_init:
	rhashtable_destroy(&vg->vlan_hash);
err_rhtbl:
err_vlan_enabled:
	kfree(vg);

	goto out;
}