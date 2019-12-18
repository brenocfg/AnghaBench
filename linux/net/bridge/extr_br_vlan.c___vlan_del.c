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
struct net_bridge_vlan_group {int /*<<< orphan*/  vlan_hash; int /*<<< orphan*/  num_vlans; } ;
struct net_bridge_vlan {int /*<<< orphan*/  rcu; int /*<<< orphan*/  vid; int /*<<< orphan*/  vnode; int /*<<< orphan*/  flags; TYPE_1__* br; struct net_bridge_vlan* brvlan; struct net_bridge_port* port; } ;
struct net_bridge_port {int /*<<< orphan*/  br; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_BRENTRY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  __vlan_del_list (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  __vlan_delete_pvid (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 int __vlan_vid_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_bridge_vlan*) ; 
 int br_switchdev_port_vlan_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* br_vlan_group (TYPE_1__*) ; 
 scalar_t__ br_vlan_is_master (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_vlan_put_master (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_vlan_rht_params ; 
 scalar_t__ br_vlan_should_use (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* nbp_vlan_group (struct net_bridge_port*) ; 
 int /*<<< orphan*/  nbp_vlan_rcu_free ; 
 int /*<<< orphan*/  nbp_vlan_set_vlan_dev_state (struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_tunnel_info_del (struct net_bridge_vlan_group*,struct net_bridge_vlan*) ; 

__attribute__((used)) static int __vlan_del(struct net_bridge_vlan *v)
{
	struct net_bridge_vlan *masterv = v;
	struct net_bridge_vlan_group *vg;
	struct net_bridge_port *p = NULL;
	int err = 0;

	if (br_vlan_is_master(v)) {
		vg = br_vlan_group(v->br);
	} else {
		p = v->port;
		vg = nbp_vlan_group(v->port);
		masterv = v->brvlan;
	}

	__vlan_delete_pvid(vg, v->vid);
	if (p) {
		err = __vlan_vid_del(p->dev, p->br, v);
		if (err)
			goto out;
	} else {
		err = br_switchdev_port_vlan_del(v->br->dev, v->vid);
		if (err && err != -EOPNOTSUPP)
			goto out;
		err = 0;
	}

	if (br_vlan_should_use(v)) {
		v->flags &= ~BRIDGE_VLAN_INFO_BRENTRY;
		vg->num_vlans--;
	}

	if (masterv != v) {
		vlan_tunnel_info_del(vg, v);
		rhashtable_remove_fast(&vg->vlan_hash, &v->vnode,
				       br_vlan_rht_params);
		__vlan_del_list(v);
		nbp_vlan_set_vlan_dev_state(p, v->vid);
		call_rcu(&v->rcu, nbp_vlan_rcu_free);
	}

	br_vlan_put_master(masterv);
out:
	return err;
}