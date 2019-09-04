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
struct sk_buff {unsigned int data_len; scalar_t__ len; int /*<<< orphan*/  head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct sk_buff* __alloc_skb (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_alloc_rx_flag (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff const*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_header (struct sk_buff*,struct sk_buff const*) ; 
 unsigned int skb_end_offset (struct sk_buff const*) ; 
 int skb_headroom (struct sk_buff const*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

struct sk_buff *skb_copy(const struct sk_buff *skb, gfp_t gfp_mask)
{
	int headerlen = skb_headroom(skb);
	unsigned int size = skb_end_offset(skb) + skb->data_len;
	struct sk_buff *n = __alloc_skb(size, gfp_mask,
					skb_alloc_rx_flag(skb), NUMA_NO_NODE);

	if (!n)
		return NULL;

	/* Set the data pointer */
	skb_reserve(n, headerlen);
	/* Set the tail pointer and length */
	skb_put(n, skb->len);

	BUG_ON(skb_copy_bits(skb, -headerlen, n->head, headerlen + skb->len));

	skb_copy_header(n, skb);
	return n;
}