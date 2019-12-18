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
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index_rcu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_do_netdev_egress (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  nft_net (struct nft_pktinfo const*) ; 

void nf_fwd_netdev_egress(const struct nft_pktinfo *pkt, int oif)
{
	struct net_device *dev;

	dev = dev_get_by_index_rcu(nft_net(pkt), oif);
	if (!dev) {
		kfree_skb(pkt->skb);
		return;
	}

	nf_do_netdev_egress(pkt->skb, dev);
}