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
struct ipv6hdr {int* flow_lbl; } ;

/* Variables and functions */

__attribute__((used)) static inline void lowpan_iphc_tf_set_ecn(struct ipv6hdr *hdr, const u8 *tf)
{
	/* get the two higher bits which is ecn */
	u8 ecn = tf[0] & 0xc0;

	/* ECN takes 0x30 in hdr->flow_lbl[0] */
	hdr->flow_lbl[0] |= (ecn >> 2);
}