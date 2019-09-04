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
struct sk_buff {int data; int /*<<< orphan*/  mac_header; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  VLAN_ETH_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,int,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_set_encap_proto (struct sk_buff*,struct vlan_hdr*) ; 

int __skb_vlan_pop(struct sk_buff *skb, u16 *vlan_tci)
{
	struct vlan_hdr *vhdr;
	int offset = skb->data - skb_mac_header(skb);
	int err;

	if (WARN_ONCE(offset,
		      "__skb_vlan_pop got skb with skb->data not at mac header (offset %d)\n",
		      offset)) {
		return -EINVAL;
	}

	err = skb_ensure_writable(skb, VLAN_ETH_HLEN);
	if (unlikely(err))
		return err;

	skb_postpull_rcsum(skb, skb->data + (2 * ETH_ALEN), VLAN_HLEN);

	vhdr = (struct vlan_hdr *)(skb->data + ETH_HLEN);
	*vlan_tci = ntohs(vhdr->h_vlan_TCI);

	memmove(skb->data + VLAN_HLEN, skb->data, 2 * ETH_ALEN);
	__skb_pull(skb, VLAN_HLEN);

	vlan_set_encap_proto(skb, vhdr);
	skb->mac_header += VLAN_HLEN;

	if (skb_network_offset(skb) < ETH_HLEN)
		skb_set_network_header(skb, ETH_HLEN);

	skb_reset_mac_len(skb);

	return err;
}