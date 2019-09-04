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
typedef  int /*<<< orphan*/  u32 ;
struct desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void debug_desc(u32 phys, struct desc *desc)
{
#if DEBUG_DESC
	printk(KERN_DEBUG "%X: %X %3X %3X %08X %2X < %2X %4X %X"
	       " %X %X %02X%02X%02X%02X%02X%02X < %02X%02X%02X%02X%02X%02X\n",
	       phys, desc->next, desc->buf_len, desc->pkt_len,
	       desc->data, desc->dest_id, desc->src_id, desc->flags,
	       desc->qos, desc->padlen, desc->vlan_tci,
	       desc->dst_mac_0, desc->dst_mac_1, desc->dst_mac_2,
	       desc->dst_mac_3, desc->dst_mac_4, desc->dst_mac_5,
	       desc->src_mac_0, desc->src_mac_1, desc->src_mac_2,
	       desc->src_mac_3, desc->src_mac_4, desc->src_mac_5);
#endif
}