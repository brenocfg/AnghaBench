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
struct sk_buff {void* data; int mac_header; } ;

/* Variables and functions */
 int ETH_TLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 void* skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_metadata_end (struct sk_buff*) ; 
 int skb_metadata_len (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *skb_reorder_vlan_header(struct sk_buff *skb)
{
	int mac_len, meta_len;
	void *meta;

	if (skb_cow(skb, skb_headroom(skb)) < 0) {
		kfree_skb(skb);
		return NULL;
	}

	mac_len = skb->data - skb_mac_header(skb);
	if (likely(mac_len > VLAN_HLEN + ETH_TLEN)) {
		memmove(skb_mac_header(skb) + VLAN_HLEN, skb_mac_header(skb),
			mac_len - VLAN_HLEN - ETH_TLEN);
	}

	meta_len = skb_metadata_len(skb);
	if (meta_len) {
		meta = skb_metadata_end(skb) - meta_len;
		memmove(meta + VLAN_HLEN, meta, meta_len);
	}

	skb->mac_header += VLAN_HLEN;
	return skb;
}