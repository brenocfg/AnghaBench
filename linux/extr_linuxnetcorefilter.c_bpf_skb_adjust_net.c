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
typedef  int u32 ;
struct sk_buff {scalar_t__ transport_header; scalar_t__ network_header; scalar_t__ protocol; int len; } ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EFAULT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int __bpf_skb_max_len (struct sk_buff*) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  bpf_compute_data_pointers (struct sk_buff*) ; 
 int bpf_skb_net_base_len (struct sk_buff*) ; 
 int bpf_skb_net_grow (struct sk_buff*,int) ; 
 int bpf_skb_net_shrink (struct sk_buff*,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int skb_network_header_len (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 scalar_t__ skb_transport_header_was_set (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_adjust_net(struct sk_buff *skb, s32 len_diff)
{
	bool trans_same = skb->transport_header == skb->network_header;
	u32 len_cur, len_diff_abs = abs(len_diff);
	u32 len_min = bpf_skb_net_base_len(skb);
	u32 len_max = __bpf_skb_max_len(skb);
	__be16 proto = skb->protocol;
	bool shrink = len_diff < 0;
	int ret;

	if (unlikely(len_diff_abs > 0xfffU))
		return -EFAULT;
	if (unlikely(proto != htons(ETH_P_IP) &&
		     proto != htons(ETH_P_IPV6)))
		return -ENOTSUPP;

	len_cur = skb->len - skb_network_offset(skb);
	if (skb_transport_header_was_set(skb) && !trans_same)
		len_cur = skb_network_header_len(skb);
	if ((shrink && (len_diff_abs >= len_cur ||
			len_cur - len_diff_abs < len_min)) ||
	    (!shrink && (skb->len + len_diff_abs > len_max &&
			 !skb_is_gso(skb))))
		return -ENOTSUPP;

	ret = shrink ? bpf_skb_net_shrink(skb, len_diff_abs) :
		       bpf_skb_net_grow(skb, len_diff_abs);

	bpf_compute_data_pointers(skb);
	return ret;
}