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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  ptype_all; } ;
struct net {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  dev_queue_xmit_nit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 struct ethhdr* skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int vrf_finish_direct(struct net *net, struct sock *sk,
			     struct sk_buff *skb)
{
	struct net_device *vrf_dev = skb->dev;

	if (!list_empty(&vrf_dev->ptype_all) &&
	    likely(skb_headroom(skb) >= ETH_HLEN)) {
		struct ethhdr *eth = skb_push(skb, ETH_HLEN);

		ether_addr_copy(eth->h_source, vrf_dev->dev_addr);
		eth_zero_addr(eth->h_dest);
		eth->h_proto = skb->protocol;

		rcu_read_lock_bh();
		dev_queue_xmit_nit(skb, vrf_dev);
		rcu_read_unlock_bh();

		skb_pull(skb, ETH_HLEN);
	}

	return 1;
}