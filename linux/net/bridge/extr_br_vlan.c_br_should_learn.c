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
struct sk_buff {scalar_t__ vlan_proto; } ;
struct net_bridge_vlan_group {int /*<<< orphan*/  num_vlans; } ;
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {scalar_t__ vlan_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_VLAN_ENABLED ; 
 int /*<<< orphan*/  br_get_pvid (struct net_bridge_vlan_group*) ; 
 int /*<<< orphan*/  br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 scalar_t__ br_vlan_find (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_get_tag (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct net_bridge_vlan_group* nbp_vlan_group_rcu (struct net_bridge_port*) ; 

bool br_should_learn(struct net_bridge_port *p, struct sk_buff *skb, u16 *vid)
{
	struct net_bridge_vlan_group *vg;
	struct net_bridge *br = p->br;

	/* If filtering was disabled at input, let it pass. */
	if (!br_opt_get(br, BROPT_VLAN_ENABLED))
		return true;

	vg = nbp_vlan_group_rcu(p);
	if (!vg || !vg->num_vlans)
		return false;

	if (!br_vlan_get_tag(skb, vid) && skb->vlan_proto != br->vlan_proto)
		*vid = 0;

	if (!*vid) {
		*vid = br_get_pvid(vg);
		if (!*vid)
			return false;

		return true;
	}

	if (br_vlan_find(vg, *vid))
		return true;

	return false;
}