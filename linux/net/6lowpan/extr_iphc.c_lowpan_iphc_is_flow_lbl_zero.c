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
struct ipv6hdr {int* flow_lbl; } ;

/* Variables and functions */

__attribute__((used)) static inline bool lowpan_iphc_is_flow_lbl_zero(const struct ipv6hdr *hdr)
{
	return ((!(hdr->flow_lbl[0] & 0x0f)) &&
		!hdr->flow_lbl[1] && !hdr->flow_lbl[2]);
}