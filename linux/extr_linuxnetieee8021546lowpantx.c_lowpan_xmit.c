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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {scalar_t__ needed_headroom; scalar_t__ needed_tailroom; TYPE_1__ stats; } ;
struct ieee802154_hdr {int dummy; } ;
typedef  scalar_t__ netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPV6_MIN_MTU ; 
 scalar_t__ NET_XMIT_DROP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ ieee802154_hdr_peek (struct sk_buff*,struct ieee802154_hdr*) ; 
 int ieee802154_max_payload (struct ieee802154_hdr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 TYPE_2__* lowpan_802154_dev (struct net_device*) ; 
 int lowpan_header (struct sk_buff*,struct net_device*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ lowpan_xmit_fragmented (struct sk_buff*,struct net_device*,struct ieee802154_hdr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int skb_network_header (struct sk_buff*) ; 
 int skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

netdev_tx_t lowpan_xmit(struct sk_buff *skb, struct net_device *ldev)
{
	struct ieee802154_hdr wpan_hdr;
	int max_single, ret;
	u16 dgram_size, dgram_offset;

	pr_debug("package xmit\n");

	WARN_ON_ONCE(skb->len > IPV6_MIN_MTU);

	/* We must take a copy of the skb before we modify/replace the ipv6
	 * header as the header could be used elsewhere
	 */
	if (unlikely(skb_headroom(skb) < ldev->needed_headroom ||
		     skb_tailroom(skb) < ldev->needed_tailroom)) {
		struct sk_buff *nskb;

		nskb = skb_copy_expand(skb, ldev->needed_headroom,
				       ldev->needed_tailroom, GFP_ATOMIC);
		if (likely(nskb)) {
			consume_skb(skb);
			skb = nskb;
		} else {
			kfree_skb(skb);
			return NET_XMIT_DROP;
		}
	} else {
		skb = skb_unshare(skb, GFP_ATOMIC);
		if (!skb)
			return NET_XMIT_DROP;
	}

	ret = lowpan_header(skb, ldev, &dgram_size, &dgram_offset);
	if (ret < 0) {
		kfree_skb(skb);
		return NET_XMIT_DROP;
	}

	if (ieee802154_hdr_peek(skb, &wpan_hdr) < 0) {
		kfree_skb(skb);
		return NET_XMIT_DROP;
	}

	max_single = ieee802154_max_payload(&wpan_hdr);

	if (skb_tail_pointer(skb) - skb_network_header(skb) <= max_single) {
		skb->dev = lowpan_802154_dev(ldev)->wdev;
		ldev->stats.tx_packets++;
		ldev->stats.tx_bytes += dgram_size;
		return dev_queue_xmit(skb);
	} else {
		netdev_tx_t rc;

		pr_debug("frame is too big, fragmentation is needed\n");
		rc = lowpan_xmit_fragmented(skb, ldev, &wpan_hdr, dgram_size,
					    dgram_offset);

		return rc < 0 ? NET_XMIT_DROP : rc;
	}
}