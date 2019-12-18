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
struct sk_buff {int /*<<< orphan*/  protocol; TYPE_1__* dev; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 void* ETH_HLEN ; 
 scalar_t__ MPLS_HLEN ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ mpls_hdr (struct sk_buff*) ; 
 int skb_ensure_writable (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mod_eth_type (struct sk_buff*,struct ethhdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_postpull_rcsum (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int skb_mpls_pop(struct sk_buff *skb, __be16 next_proto, int mac_len)
{
	int err;

	if (unlikely(!eth_p_mpls(skb->protocol)))
		return 0;

	err = skb_ensure_writable(skb, mac_len + MPLS_HLEN);
	if (unlikely(err))
		return err;

	skb_postpull_rcsum(skb, mpls_hdr(skb), MPLS_HLEN);
	memmove(skb_mac_header(skb) + MPLS_HLEN, skb_mac_header(skb),
		mac_len);

	__skb_pull(skb, MPLS_HLEN);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, mac_len);

	if (skb->dev && skb->dev->type == ARPHRD_ETHER) {
		struct ethhdr *hdr;

		/* use mpls_hdr() to get ethertype to account for VLANs. */
		hdr = (struct ethhdr *)((void *)mpls_hdr(skb) - ETH_HLEN);
		skb_mod_eth_type(skb, hdr, next_proto);
	}
	skb->protocol = next_proto;

	return 0;
}