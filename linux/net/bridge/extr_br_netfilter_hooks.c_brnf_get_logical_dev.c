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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct brnf_net {scalar_t__ pass_vlan_indev; } ;

/* Variables and functions */
 int VLAN_VID_MASK ; 
 struct net_device* __vlan_find_dev_deep_rcu (struct net_device*,int /*<<< orphan*/ ,int) ; 
 struct net_device* bridge_parent (struct net_device const*) ; 
 int /*<<< orphan*/  brnf_net_id ; 
 struct brnf_net* net_generic (struct net const*,int /*<<< orphan*/ ) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static struct net_device *brnf_get_logical_dev(struct sk_buff *skb,
					       const struct net_device *dev,
					       const struct net *net)
{
	struct net_device *vlan, *br;
	struct brnf_net *brnet = net_generic(net, brnf_net_id);

	br = bridge_parent(dev);

	if (brnet->pass_vlan_indev == 0 || !skb_vlan_tag_present(skb))
		return br;

	vlan = __vlan_find_dev_deep_rcu(br, skb->vlan_proto,
				    skb_vlan_tag_get(skb) & VLAN_VID_MASK);

	return vlan ? vlan : br;
}