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
struct sr6_tlv_t {scalar_t__ type; int len; int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct ip6_t {int dummy; } ;
struct ip6_srh_t {int first_segment; } ;
struct ip6_addr_t {scalar_t__ type; int len; int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ SR6_TLV_EGRESS ; 
 scalar_t__ bpf_skb_load_bytes (struct __sk_buff*,int,struct sr6_tlv_t*,int) ; 
 int ntohll (int /*<<< orphan*/ ) ; 

__attribute__((always_inline))
int has_egr_tlv(struct __sk_buff *skb, struct ip6_srh_t *srh)
{
	int tlv_offset = sizeof(struct ip6_t) + sizeof(struct ip6_srh_t) +
		((srh->first_segment + 1) << 4);
	struct sr6_tlv_t tlv;

	if (bpf_skb_load_bytes(skb, tlv_offset, &tlv, sizeof(struct sr6_tlv_t)))
		return 0;

	if (tlv.type == SR6_TLV_EGRESS && tlv.len == 18) {
		struct ip6_addr_t egr_addr;

		if (bpf_skb_load_bytes(skb, tlv_offset + 4, &egr_addr, 16))
			return 0;

		// check if egress TLV value is correct
		if (ntohll(egr_addr.hi) == 0xfd00000000000000 &&
				ntohll(egr_addr.lo) == 0x4)
			return 1;
	}

	return 0;
}