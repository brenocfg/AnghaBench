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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ csum_offset; scalar_t__ csum_start; int /*<<< orphan*/  ip_summed; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_PARTIAL ; 
 scalar_t__ U16_MAX ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

bool skb_partial_csum_set(struct sk_buff *skb, u16 start, u16 off)
{
	u32 csum_end = (u32)start + (u32)off + sizeof(__sum16);
	u32 csum_start = skb_headroom(skb) + (u32)start;

	if (unlikely(csum_start > U16_MAX || csum_end > skb_headlen(skb))) {
		net_warn_ratelimited("bad partial csum: csum=%u/%u headroom=%u headlen=%u\n",
				     start, off, skb_headroom(skb), skb_headlen(skb));
		return false;
	}
	skb->ip_summed = CHECKSUM_PARTIAL;
	skb->csum_start = csum_start;
	skb->csum_offset = off;
	skb_set_transport_header(skb, start);
	return true;
}