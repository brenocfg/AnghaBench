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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  mac_len; int /*<<< orphan*/  inner_protocol; scalar_t__ encapsulation; } ;
struct ovs_action_push_mpls {int /*<<< orphan*/  mpls_ethertype; int /*<<< orphan*/  mpls_lse; } ;
struct mpls_shim_hdr {int /*<<< orphan*/  label_stack_entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 scalar_t__ MAC_PROTO_ETHERNET ; 
 scalar_t__ MPLS_HLEN ; 
 int /*<<< orphan*/  eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  invalidate_flow_key (struct sw_flow_key*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mpls_shim_hdr* mpls_hdr (struct sk_buff*) ; 
 scalar_t__ ovs_key_mac_proto (struct sw_flow_key*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_postpush_rcsum (struct sk_buff*,struct mpls_shim_hdr*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_inner_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_inner_protocol (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ethertype (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_mpls(struct sk_buff *skb, struct sw_flow_key *key,
		     const struct ovs_action_push_mpls *mpls)
{
	struct mpls_shim_hdr *new_mpls_lse;

	/* Networking stack do not allow simultaneous Tunnel and MPLS GSO. */
	if (skb->encapsulation)
		return -ENOTSUPP;

	if (skb_cow_head(skb, MPLS_HLEN) < 0)
		return -ENOMEM;

	if (!skb->inner_protocol) {
		skb_set_inner_network_header(skb, skb->mac_len);
		skb_set_inner_protocol(skb, skb->protocol);
	}

	skb_push(skb, MPLS_HLEN);
	memmove(skb_mac_header(skb) - MPLS_HLEN, skb_mac_header(skb),
		skb->mac_len);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, skb->mac_len);

	new_mpls_lse = mpls_hdr(skb);
	new_mpls_lse->label_stack_entry = mpls->mpls_lse;

	skb_postpush_rcsum(skb, new_mpls_lse, MPLS_HLEN);

	if (ovs_key_mac_proto(key) == MAC_PROTO_ETHERNET)
		update_ethertype(skb, eth_hdr(skb), mpls->mpls_ethertype);
	skb->protocol = mpls->mpls_ethertype;

	invalidate_flow_key(key);
	return 0;
}