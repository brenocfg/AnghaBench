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
struct sk_buff {int dummy; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_do_netdev_egress (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 
 struct sk_buff* skb_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nf_dup_netdev_egress(const struct nft_pktinfo *pkt, int oif)
{
	struct net_device *dev;
	struct sk_buff *skb;

	dev = dev_get_by_index_rcu(nft_net(pkt), oif);
	if (dev == NULL)
		return;

	skb = skb_clone(pkt->skb, GFP_ATOMIC);
	if (skb)
		nf_do_netdev_egress(skb, dev);
}