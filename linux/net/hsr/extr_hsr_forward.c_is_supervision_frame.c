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
struct sk_buff {int dummy; } ;
struct hsr_sup_tag {scalar_t__ HSR_TLV_type; int HSR_TLV_length; } ;
struct TYPE_2__ {scalar_t__ encap_proto; } ;
struct hsrv1_ethhdr_sp {struct hsr_sup_tag hsr_sup; TYPE_1__ hsr; } ;
struct hsrv0_ethhdr_sp {struct hsr_sup_tag hsr_sup; } ;
struct hsr_sup_payload {int dummy; } ;
struct hsr_priv {int /*<<< orphan*/  sup_multicast_addr; } ;
struct ethhdr {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_HSR ; 
 int /*<<< orphan*/  ETH_P_PRP ; 
 scalar_t__ HSR_TLV_ANNOUNCE ; 
 scalar_t__ HSR_TLV_LIFE_CHECK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 

__attribute__((used)) static bool is_supervision_frame(struct hsr_priv *hsr, struct sk_buff *skb)
{
	struct ethhdr *eth_hdr;
	struct hsr_sup_tag *hsr_sup_tag;
	struct hsrv1_ethhdr_sp *hsr_V1_hdr;

	WARN_ON_ONCE(!skb_mac_header_was_set(skb));
	eth_hdr = (struct ethhdr *)skb_mac_header(skb);

	/* Correct addr? */
	if (!ether_addr_equal(eth_hdr->h_dest,
			      hsr->sup_multicast_addr))
		return false;

	/* Correct ether type?. */
	if (!(eth_hdr->h_proto == htons(ETH_P_PRP) ||
	      eth_hdr->h_proto == htons(ETH_P_HSR)))
		return false;

	/* Get the supervision header from correct location. */
	if (eth_hdr->h_proto == htons(ETH_P_HSR)) { /* Okay HSRv1. */
		hsr_V1_hdr = (struct hsrv1_ethhdr_sp *)skb_mac_header(skb);
		if (hsr_V1_hdr->hsr.encap_proto != htons(ETH_P_PRP))
			return false;

		hsr_sup_tag = &hsr_V1_hdr->hsr_sup;
	} else {
		hsr_sup_tag =
		     &((struct hsrv0_ethhdr_sp *)skb_mac_header(skb))->hsr_sup;
	}

	if (hsr_sup_tag->HSR_TLV_type != HSR_TLV_ANNOUNCE &&
	    hsr_sup_tag->HSR_TLV_type != HSR_TLV_LIFE_CHECK)
		return false;
	if (hsr_sup_tag->HSR_TLV_length != 12 &&
	    hsr_sup_tag->HSR_TLV_length != sizeof(struct hsr_sup_payload))
		return false;

	return true;
}