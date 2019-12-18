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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_hdr {int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_reorder_vlan_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_set_encap_proto (struct sk_buff*,struct vlan_hdr*) ; 

struct sk_buff *skb_vlan_untag(struct sk_buff *skb)
{
	struct vlan_hdr *vhdr;
	u16 vlan_tci;

	if (unlikely(skb_vlan_tag_present(skb))) {
		/* vlan_tci is already set-up so leave this for another time */
		return skb;
	}

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (unlikely(!skb))
		goto err_free;

	if (unlikely(!pskb_may_pull(skb, VLAN_HLEN)))
		goto err_free;

	vhdr = (struct vlan_hdr *)skb->data;
	vlan_tci = ntohs(vhdr->h_vlan_TCI);
	__vlan_hwaccel_put_tag(skb, skb->protocol, vlan_tci);

	skb_pull_rcsum(skb, VLAN_HLEN);
	vlan_set_encap_proto(skb, vhdr);

	skb = skb_reorder_vlan_header(skb);
	if (unlikely(!skb))
		goto err_free;

	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_mac_len(skb);

	return skb;

err_free:
	kfree_skb(skb);
	return NULL;
}