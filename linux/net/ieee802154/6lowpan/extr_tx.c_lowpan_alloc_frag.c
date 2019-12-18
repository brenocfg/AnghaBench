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
struct sk_buff {int /*<<< orphan*/  mac_len; int /*<<< orphan*/  priority; struct net_device* dev; } ;
struct net_device {scalar_t__ needed_headroom; scalar_t__ needed_tailroom; } ;
struct ieee802154_hdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct TYPE_2__ {struct net_device* wdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 TYPE_1__* lowpan_802154_dev (struct net_device*) ; 
 int /*<<< orphan*/ * mac_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int wpan_dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct sk_buff*
lowpan_alloc_frag(struct sk_buff *skb, int size,
		  const struct ieee802154_hdr *master_hdr, bool frag1)
{
	struct net_device *wdev = lowpan_802154_dev(skb->dev)->wdev;
	struct sk_buff *frag;
	int rc;

	frag = alloc_skb(wdev->needed_headroom + wdev->needed_tailroom + size,
			 GFP_ATOMIC);

	if (likely(frag)) {
		frag->dev = wdev;
		frag->priority = skb->priority;
		skb_reserve(frag, wdev->needed_headroom);
		skb_reset_network_header(frag);
		*mac_cb(frag) = *mac_cb(skb);

		if (frag1) {
			skb_put_data(frag, skb_mac_header(skb), skb->mac_len);
		} else {
			rc = wpan_dev_hard_header(frag, wdev,
						  &master_hdr->dest,
						  &master_hdr->source, size);
			if (rc < 0) {
				kfree_skb(frag);
				return ERR_PTR(rc);
			}
		}
	} else {
		frag = ERR_PTR(-ENOMEM);
	}

	return frag;
}