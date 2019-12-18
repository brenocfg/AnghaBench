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

__attribute__((used)) static inline void lowpan_iphc_tf_set_dscp(struct ipv6hdr *hdr, const u8 *tf)
{
	/* DSCP is at place after ECN */
	u8 dscp = tf[0] & 0x3f;

	/* The four highest bits need to be set at hdr->priority */
	hdr->priority |= ((dscp & 0x3c) >> 2);
	/* The two lower bits is part of hdr->flow_lbl[0] */
	hdr->flow_lbl[0] |= ((dscp & 0x03) << 6);
}