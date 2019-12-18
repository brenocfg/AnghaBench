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
struct sk_buff {scalar_t__ pkt_type; } ;
struct packet_type {int dummy; } ;
struct net_device {int flags; scalar_t__ addr_len; } ;
struct neighbour_cb {int dummy; } ;
struct arphdr {scalar_t__ ar_hln; int ar_pln; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  NEIGH_CB (struct sk_buff*) ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  NFPROTO_ARP ; 
 int /*<<< orphan*/  NF_ARP_IN ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PACKET_LOOPBACK ; 
 scalar_t__ PACKET_OTHERHOST ; 
 struct arphdr* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  arp_hdr_len (struct net_device*) ; 
 int /*<<< orphan*/  arp_process ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arp_rcv(struct sk_buff *skb, struct net_device *dev,
		   struct packet_type *pt, struct net_device *orig_dev)
{
	const struct arphdr *arp;

	/* do not tweak dropwatch on an ARP we will ignore */
	if (dev->flags & IFF_NOARP ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    skb->pkt_type == PACKET_LOOPBACK)
		goto consumeskb;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out_of_mem;

	/* ARP header, plus 2 device addresses, plus 2 IP addresses.  */
	if (!pskb_may_pull(skb, arp_hdr_len(dev)))
		goto freeskb;

	arp = arp_hdr(skb);
	if (arp->ar_hln != dev->addr_len || arp->ar_pln != 4)
		goto freeskb;

	memset(NEIGH_CB(skb), 0, sizeof(struct neighbour_cb));

	return NF_HOOK(NFPROTO_ARP, NF_ARP_IN,
		       dev_net(dev), NULL, skb, dev, NULL,
		       arp_process);

consumeskb:
	consume_skb(skb);
	return NET_RX_SUCCESS;
freeskb:
	kfree_skb(skb);
out_of_mem:
	return NET_RX_DROP;
}