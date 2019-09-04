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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net_bridge_vlan_group {int dummy; } ;
struct net_bridge_port {TYPE_1__* br; struct net_device* dev; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  NFPROTO_BRIDGE ; 
 int NF_BR_FORWARD ; 
 int NF_BR_LOCAL_OUT ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int,struct net*,int /*<<< orphan*/ *,struct sk_buff*,struct net_device*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_forward_finish ; 
 struct sk_buff* br_handle_vlan (TYPE_1__*,struct net_bridge_port const*,struct net_bridge_vlan_group*,struct sk_buff*) ; 
 int /*<<< orphan*/  br_netpoll_send_skb (struct net_bridge_port const*,struct sk_buff*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  is_skb_forwardable (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct net_bridge_vlan_group* nbp_vlan_group_rcu (struct net_bridge_port const*) ; 
 int /*<<< orphan*/  netpoll_tx_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_forward_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_warn_if_lro (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __br_forward(const struct net_bridge_port *to,
			 struct sk_buff *skb, bool local_orig)
{
	struct net_bridge_vlan_group *vg;
	struct net_device *indev;
	struct net *net;
	int br_hook;

	vg = nbp_vlan_group_rcu(to);
	skb = br_handle_vlan(to->br, to, vg, skb);
	if (!skb)
		return;

	indev = skb->dev;
	skb->dev = to->dev;
	if (!local_orig) {
		if (skb_warn_if_lro(skb)) {
			kfree_skb(skb);
			return;
		}
		br_hook = NF_BR_FORWARD;
		skb_forward_csum(skb);
		net = dev_net(indev);
	} else {
		if (unlikely(netpoll_tx_running(to->br->dev))) {
			skb_push(skb, ETH_HLEN);
			if (!is_skb_forwardable(skb->dev, skb))
				kfree_skb(skb);
			else
				br_netpoll_send_skb(to, skb);
			return;
		}
		br_hook = NF_BR_LOCAL_OUT;
		net = dev_net(skb->dev);
		indev = NULL;
	}

	NF_HOOK(NFPROTO_BRIDGE, br_hook,
		net, NULL, skb, indev, skb->dev,
		br_forward_finish);
}