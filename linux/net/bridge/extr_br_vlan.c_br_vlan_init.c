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
struct net_bridge_vlan_group {int /*<<< orphan*/  vlan_hash; int /*<<< orphan*/  vlan_list; } ;
struct net_bridge {int default_pvid; int /*<<< orphan*/  vlgrp; int /*<<< orphan*/  vlan_proto; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_vlan_rht_params ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_vlan_group*) ; 
 struct net_bridge_vlan_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_bridge_vlan_group*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlan_tunnel_init (struct net_bridge_vlan_group*) ; 

int br_vlan_init(struct net_bridge *br)
{
	struct net_bridge_vlan_group *vg;
	int ret = -ENOMEM;

	vg = kzalloc(sizeof(*vg), GFP_KERNEL);
	if (!vg)
		goto out;
	ret = rhashtable_init(&vg->vlan_hash, &br_vlan_rht_params);
	if (ret)
		goto err_rhtbl;
	ret = vlan_tunnel_init(vg);
	if (ret)
		goto err_tunnel_init;
	INIT_LIST_HEAD(&vg->vlan_list);
	br->vlan_proto = htons(ETH_P_8021Q);
	br->default_pvid = 1;
	rcu_assign_pointer(br->vlgrp, vg);

out:
	return ret;

err_tunnel_init:
	rhashtable_destroy(&vg->vlan_hash);
err_rhtbl:
	kfree(vg);

	goto out;
}