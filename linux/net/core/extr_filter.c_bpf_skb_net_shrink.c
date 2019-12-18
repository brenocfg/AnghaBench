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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct skb_shared_info {int gso_type; scalar_t__ gso_segs; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int BPF_F_ADJ_ROOM_FIXED_GSO ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SKB_GSO_DODGY ; 
 int SKB_GSO_UDP_L4 ; 
 int bpf_skb_net_hdr_pop (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_increase_gso_size (struct skb_shared_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso_tcp (struct sk_buff*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 int skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bpf_skb_net_shrink(struct sk_buff *skb, u32 off, u32 len_diff,
			      u64 flags)
{
	int ret;

	if (flags & ~BPF_F_ADJ_ROOM_FIXED_GSO)
		return -EINVAL;

	if (skb_is_gso(skb) && !skb_is_gso_tcp(skb)) {
		/* udp gso_size delineates datagrams, only allow if fixed */
		if (!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ||
		    !(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			return -ENOTSUPP;
	}

	ret = skb_unclone(skb, GFP_ATOMIC);
	if (unlikely(ret < 0))
		return ret;

	ret = bpf_skb_net_hdr_pop(skb, off, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (skb_is_gso(skb)) {
		struct skb_shared_info *shinfo = skb_shinfo(skb);

		/* Due to header shrink, MSS can be upgraded. */
		if (!(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			skb_increase_gso_size(shinfo, len_diff);

		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	}

	return 0;
}