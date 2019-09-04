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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ mac_len; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 void* ETH_HLEN ; 
 scalar_t__ MAC_PROTO_ETHERNET ; 
 scalar_t__ MPLS_HLEN ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mpls_hdr (struct sk_buff*) ; 
 scalar_t__ ovs_key_mac_proto (struct sw_flow_key*) ; 
 int skb_ensure_writable (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_ethertype (struct sk_buff*,struct ethhdr*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int pop_mpls(struct sk_buff *skb, struct sw_flow_key *key,
		    const __be16 ethertype)
{
	int err;

	err = skb_ensure_writable(skb, skb->mac_len + MPLS_HLEN);
	if (unlikely(err))
		return err;

	skb_postpull_rcsum(skb, mpls_hdr(skb), MPLS_HLEN);

	memmove(skb_mac_header(skb) + MPLS_HLEN, skb_mac_header(skb),
		skb->mac_len);

	__skb_pull(skb, MPLS_HLEN);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb->mac_len);

	if (ovs_key_mac_proto(key) == MAC_PROTO_ETHERNET) {
		struct ethhdr *hdr;

		/* mpls_hdr() is used to locate the ethertype field correctly in the
		 * presence of VLAN tags.
		 */
		hdr = (struct ethhdr *)((void *)mpls_hdr(skb) - ETH_HLEN);
		update_ethertype(skb, hdr, ethertype);
	}
	if (eth_p_mpls(skb->protocol))
		skb->protocol = ethertype;

	invalidate_flow_key(key);
	return 0;
}