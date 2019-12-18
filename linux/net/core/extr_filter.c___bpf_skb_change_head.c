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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ __bpf_skb_max_len (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int skb_cow (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int __bpf_skb_change_head(struct sk_buff *skb, u32 head_room,
					u64 flags)
{
	u32 max_len = __bpf_skb_max_len(skb);
	u32 new_len = skb->len + head_room;
	int ret;

	if (unlikely(flags || (!skb_is_gso(skb) && new_len > max_len) ||
		     new_len < skb->len))
		return -EINVAL;

	ret = skb_cow(skb, head_room);
	if (likely(!ret)) {
		/* Idea for this helper is that we currently only
		 * allow to expand on mac header. This means that
		 * skb->protocol network header, etc, stay as is.
		 * Compared to bpf_skb_change_tail(), we're more
		 * flexible due to not needing to linearize or
		 * reset GSO. Intention for this helper is to be
		 * used by an L3 skb that needs to push mac header
		 * for redirection into L2 device.
		 */
		__skb_push(skb, head_room);
		memset(skb->data, 0, head_room);
		skb_reset_mac_header(skb);
	}

	return ret;
}