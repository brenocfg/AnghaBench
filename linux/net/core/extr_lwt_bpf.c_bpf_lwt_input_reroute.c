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
struct sk_buff {scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int (* ipv6_route_input ) (struct sk_buff*) ;} ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dst_input (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_route_input_noref (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_2__* ipv6_stub ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static int bpf_lwt_input_reroute(struct sk_buff *skb)
{
	int err = -EINVAL;

	if (skb->protocol == htons(ETH_P_IP)) {
		struct net_device *dev = skb_dst(skb)->dev;
		struct iphdr *iph = ip_hdr(skb);

		dev_hold(dev);
		skb_dst_drop(skb);
		err = ip_route_input_noref(skb, iph->daddr, iph->saddr,
					   iph->tos, dev);
		dev_put(dev);
	} else if (skb->protocol == htons(ETH_P_IPV6)) {
		skb_dst_drop(skb);
		err = ipv6_stub->ipv6_route_input(skb);
	} else {
		err = -EAFNOSUPPORT;
	}

	if (err)
		goto err;
	return dst_input(skb);

err:
	kfree_skb(skb);
	return err;
}