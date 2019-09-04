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
struct sk_buff {int /*<<< orphan*/  vlan_proto; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 struct sk_buff* __vlan_hwaccel_push_inside (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_hw_offload_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *validate_xmit_vlan(struct sk_buff *skb,
					  netdev_features_t features)
{
	if (skb_vlan_tag_present(skb) &&
	    !vlan_hw_offload_capable(features, skb->vlan_proto))
		skb = __vlan_hwaccel_push_inside(skb);
	return skb;
}