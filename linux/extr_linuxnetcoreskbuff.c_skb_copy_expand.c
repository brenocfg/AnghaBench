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
struct sk_buff {scalar_t__ len; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct sk_buff* __alloc_skb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_alloc_rx_flag (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_header (struct sk_buff*,struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_headers_offset_update (struct sk_buff*,int) ; 
 int skb_headroom (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *skb_copy_expand(const struct sk_buff *skb,
				int newheadroom, int newtailroom,
				gfp_t gfp_mask)
{
	/*
	 *	Allocate the copy buffer
	 */
	struct sk_buff *n = __alloc_skb(newheadroom + skb->len + newtailroom,
					gfp_mask, skb_alloc_rx_flag(skb),
					NUMA_NO_NODE);
	int oldheadroom = skb_headroom(skb);
	int head_copy_len, head_copy_off;

	if (!n)
		return NULL;

	skb_reserve(n, newheadroom);

	/* Set the tail pointer and length */
	skb_put(n, skb->len);

	head_copy_len = oldheadroom;
	head_copy_off = 0;
	if (newheadroom <= head_copy_len)
		head_copy_len = newheadroom;
	else
		head_copy_off = newheadroom - head_copy_len;

	/* Copy the linear header and data. */
	BUG_ON(skb_copy_bits(skb, -head_copy_len, n->head + head_copy_off,
			     skb->len + head_copy_len));

	skb_copy_header(n, skb);

	skb_headers_offset_update(n, newheadroom - oldheadroom);

	return n;
}