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
typedef  int /*<<< orphan*/  tc ;
struct ipv6hdr {int* flow_lbl; } ;

/* Variables and functions */
 int LOWPAN_IPHC_TF_00 ; 
 int LOWPAN_IPHC_TF_01 ; 
 int LOWPAN_IPHC_TF_10 ; 
 int LOWPAN_IPHC_TF_11 ; 
 int lowpan_iphc_get_tc (struct ipv6hdr const*) ; 
 scalar_t__ lowpan_iphc_is_flow_lbl_zero (struct ipv6hdr const*) ; 
 int /*<<< orphan*/  lowpan_push_hc_data (int**,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static u8 lowpan_iphc_tf_compress(u8 **hc_ptr, const struct ipv6hdr *hdr)
{
	/* get ecn dscp data in a byteformat as: ECN(hi) + DSCP(lo) */
	u8 tc = lowpan_iphc_get_tc(hdr), tf[4], val;

	/* printout the traffic class in hc format */
	pr_debug("tc 0x%02x\n", tc);

	if (lowpan_iphc_is_flow_lbl_zero(hdr)) {
		if (!tc) {
			/* 11:  Traffic Class and Flow Label are elided. */
			val = LOWPAN_IPHC_TF_11;
		} else {
			/* 10:  ECN + DSCP (1 byte), Flow Label is elided.
			 *
			 *  0 1 2 3 4 5 6 7
			 * +-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |
			 * +-+-+-+-+-+-+-+-+
			 */
			lowpan_push_hc_data(hc_ptr, &tc, sizeof(tc));
			val = LOWPAN_IPHC_TF_10;
		}
	} else {
		/* check if dscp is zero, it's after the first two bit */
		if (!(tc & 0x3f)) {
			/* 01:  ECN + 2-bit Pad + Flow Label (3 bytes), DSCP is elided
			 *
			 *                     1                   2
			 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|rsv|             Flow Label                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			memcpy(&tf[0], &hdr->flow_lbl[0], 3);
			/* zero the highest 4-bits, contains DCSP + ECN */
			tf[0] &= ~0xf0;
			/* set ECN */
			tf[0] |= (tc & 0xc0);

			lowpan_push_hc_data(hc_ptr, tf, 3);
			val = LOWPAN_IPHC_TF_01;
		} else {
			/* 00:  ECN + DSCP + 4-bit Pad + Flow Label (4 bytes)
			 *
			 *                      1                   2                   3
			 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |  rsv  |             Flow Label                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			memcpy(&tf[0], &tc, sizeof(tc));
			/* highest nibble of flow_lbl[0] is part of DSCP + ECN
			 * which will be the 4-bit pad and will be filled with
			 * zeros afterwards.
			 */
			memcpy(&tf[1], &hdr->flow_lbl[0], 3);
			/* zero the 4-bit pad, which is reserved */
			tf[1] &= ~0xf0;

			lowpan_push_hc_data(hc_ptr, tf, 4);
			val = LOWPAN_IPHC_TF_00;
		}
	}

	return val;
}