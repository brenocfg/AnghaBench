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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_vlan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_filtered; } ;

/* Variables and functions */
 TYPE_1__* BR_INPUT_SKB_CB (struct sk_buff const*) ; 
 struct net_bridge_vlan* br_vlan_find (struct net_bridge_vlan_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_vlan_get_tag (struct sk_buff const*,int /*<<< orphan*/ *) ; 
 scalar_t__ br_vlan_should_use (struct net_bridge_vlan const*) ; 

bool br_allowed_egress(struct net_bridge_vlan_group *vg,
		       const struct sk_buff *skb)
{
	const struct net_bridge_vlan *v;
	u16 vid;

	/* If this packet was not filtered at input, let it pass */
	if (!BR_INPUT_SKB_CB(skb)->vlan_filtered)
		return true;

	br_vlan_get_tag(skb, &vid);
	v = br_vlan_find(vg, vid);
	if (v && br_vlan_should_use(v))
		return true;

	return false;
}