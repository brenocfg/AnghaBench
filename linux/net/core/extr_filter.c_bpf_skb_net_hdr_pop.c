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
struct sk_buff {scalar_t__ transport_header; scalar_t__ network_header; int /*<<< orphan*/  mac_header; } ;

/* Variables and functions */
 int bpf_skb_generic_pop (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int bpf_skb_net_hdr_pop(struct sk_buff *skb, u32 off, u32 len)
{
	bool trans_same = skb->transport_header == skb->network_header;
	int ret;

	/* Same here, __skb_push()/__skb_pull() pair not needed. */
	ret = bpf_skb_generic_pop(skb, off, len);
	if (likely(!ret)) {
		skb->mac_header += len;
		skb->network_header += len;
		if (trans_same)
			skb->transport_header = skb->network_header;
	}

	return ret;
}