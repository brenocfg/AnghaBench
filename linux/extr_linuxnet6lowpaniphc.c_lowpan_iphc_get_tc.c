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
typedef  int u8 ;
struct ipv6hdr {int priority; int* flow_lbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static inline u8 lowpan_iphc_get_tc(const struct ipv6hdr *hdr)
{
	u8 dscp, ecn;

	/* hdr->priority contains the higher bits of dscp, lower are part of
	 * flow_lbl[0]. Note ECN, DCSP is swapped in ipv6 hdr.
	 */
	dscp = (hdr->priority << 2) | ((hdr->flow_lbl[0] & 0xc0) >> 6);
	/* ECN is at the two lower bits from first nibble of flow_lbl[0] */
	ecn = (hdr->flow_lbl[0] & 0x30);
	/* for pretty debug output, also shift ecn to get the ecn value */
	pr_debug("ecn 0x%02x dscp 0x%02x\n", ecn >> 4, dscp);
	/* ECN is at 0x30 now, shift it to have ECN + DCSP */
	return (ecn << 2) | dscp;
}