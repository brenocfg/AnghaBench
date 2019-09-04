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
struct skb_shared_info {scalar_t__ gso_segs; int /*<<< orphan*/  gso_type; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SKB_GSO_DODGY ; 
 scalar_t__ bpf_skb_net_base_len (struct sk_buff*) ; 
 int bpf_skb_net_hdr_pop (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_increase_gso_size (struct skb_shared_info*,scalar_t__) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso_tcp (struct sk_buff*) ; 
 scalar_t__ skb_mac_header_len (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 int skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_net_shrink(struct sk_buff *skb, u32 len_diff)
{
	u32 off = skb_mac_header_len(skb) + bpf_skb_net_base_len(skb);
	int ret;

	if (skb_is_gso(skb) && !skb_is_gso_tcp(skb))
		return -ENOTSUPP;

	ret = skb_unclone(skb, GFP_ATOMIC);
	if (unlikely(ret < 0))
		return ret;

	ret = bpf_skb_net_hdr_pop(skb, off, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (skb_is_gso(skb)) {
		struct skb_shared_info *shinfo = skb_shinfo(skb);

		/* Due to header shrink, MSS can be upgraded. */
		skb_increase_gso_size(shinfo, len_diff);
		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	}

	return 0;
}