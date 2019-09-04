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
struct sk_buff {scalar_t__ pkt_type; struct net_device* dev; } ;
struct packet_type {int dummy; } ;
struct net_device {scalar_t__ type; TYPE_1__* ieee802154_ptr; } ;
struct TYPE_2__ {struct net_device* lowpan_dev; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int lowpan_invoke_rx_handlers (struct sk_buff*) ; 
 scalar_t__ lowpan_is_frag1 (int /*<<< orphan*/ ) ; 
 scalar_t__ lowpan_is_iphc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowpan_rx_h_check (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lowpan_rcv(struct sk_buff *skb, struct net_device *wdev,
		      struct packet_type *pt, struct net_device *orig_wdev)
{
	struct net_device *ldev;

	if (wdev->type != ARPHRD_IEEE802154 ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    !lowpan_rx_h_check(skb))
		goto drop;

	ldev = wdev->ieee802154_ptr->lowpan_dev;
	if (!ldev || !netif_running(ldev))
		goto drop;

	/* Replacing skb->dev and followed rx handlers will manipulate skb. */
	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;
	skb->dev = ldev;

	/* When receive frag1 it's likely that we manipulate the buffer.
	 * When recevie iphc we manipulate the data buffer. So we need
	 * to unshare the buffer.
	 */
	if (lowpan_is_frag1(*skb_network_header(skb)) ||
	    lowpan_is_iphc(*skb_network_header(skb))) {
		skb = skb_unshare(skb, GFP_ATOMIC);
		if (!skb)
			goto out;
	}

	return lowpan_invoke_rx_handlers(skb);

drop:
	kfree_skb(skb);
out:
	return NET_RX_DROP;
}