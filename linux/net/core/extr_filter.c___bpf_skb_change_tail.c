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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ encapsulation; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ __bpf_skb_max_len (struct sk_buff*) ; 
 scalar_t__ __bpf_skb_min_len (struct sk_buff*) ; 
 int __bpf_try_make_writable (struct sk_buff*,scalar_t__) ; 
 int bpf_skb_grow_rcsum (struct sk_buff*,scalar_t__) ; 
 int bpf_skb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_gso_reset (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __bpf_skb_change_tail(struct sk_buff *skb, u32 new_len,
					u64 flags)
{
	u32 max_len = __bpf_skb_max_len(skb);
	u32 min_len = __bpf_skb_min_len(skb);
	int ret;

	if (unlikely(flags || new_len > max_len || new_len < min_len))
		return -EINVAL;
	if (skb->encapsulation)
		return -ENOTSUPP;

	/* The basic idea of this helper is that it's performing the
	 * needed work to either grow or trim an skb, and eBPF program
	 * rewrites the rest via helpers like bpf_skb_store_bytes(),
	 * bpf_lX_csum_replace() and others rather than passing a raw
	 * buffer here. This one is a slow path helper and intended
	 * for replies with control messages.
	 *
	 * Like in bpf_skb_change_proto(), we want to keep this rather
	 * minimal and without protocol specifics so that we are able
	 * to separate concerns as in bpf_skb_store_bytes() should only
	 * be the one responsible for writing buffers.
	 *
	 * It's really expected to be a slow path operation here for
	 * control message replies, so we're implicitly linearizing,
	 * uncloning and drop offloads from the skb by this.
	 */
	ret = __bpf_try_make_writable(skb, skb->len);
	if (!ret) {
		if (new_len > skb->len)
			ret = bpf_skb_grow_rcsum(skb, new_len);
		else if (new_len < skb->len)
			ret = bpf_skb_trim_rcsum(skb, new_len);
		if (!ret && skb_is_gso(skb))
			skb_gso_reset(skb);
	}
	return ret;
}