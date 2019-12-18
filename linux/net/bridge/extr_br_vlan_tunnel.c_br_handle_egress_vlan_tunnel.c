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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tunnel_dst; int /*<<< orphan*/  tunnel_id; } ;
struct net_bridge_vlan {TYPE_2__ tinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_vlan_pop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int br_handle_egress_vlan_tunnel(struct sk_buff *skb,
				 struct net_bridge_vlan *vlan)
{
	int err;

	if (!vlan || !vlan->tinfo.tunnel_id)
		return 0;

	if (unlikely(!skb_vlan_tag_present(skb)))
		return 0;

	skb_dst_drop(skb);
	err = skb_vlan_pop(skb);
	if (err)
		return err;

	skb_dst_set(skb, dst_clone(&vlan->tinfo.tunnel_dst->dst));

	return 0;
}