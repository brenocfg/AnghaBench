#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data_len; int /*<<< orphan*/  truesize; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/  frag_list; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int SKB_ALLOC_FCLONE ; 
 struct sk_buff* __alloc_skb (unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int skb_alloc_rx_flag (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_clone_fraglist (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_frag_ref (struct sk_buff*,int) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 
 int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_orphan_frags (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_zerocopy_clone (struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ ) ; 

struct sk_buff *__pskb_copy_fclone(struct sk_buff *skb, int headroom,
				   gfp_t gfp_mask, bool fclone)
{
	unsigned int size = skb_headlen(skb) + headroom;
	int flags = skb_alloc_rx_flag(skb) | (fclone ? SKB_ALLOC_FCLONE : 0);
	struct sk_buff *n = __alloc_skb(size, gfp_mask, flags, NUMA_NO_NODE);

	if (!n)
		goto out;

	/* Set the data pointer */
	skb_reserve(n, headroom);
	/* Set the tail pointer and length */
	skb_put(n, skb_headlen(skb));
	/* Copy the bytes */
	skb_copy_from_linear_data(skb, n->data, n->len);

	n->truesize += skb->data_len;
	n->data_len  = skb->data_len;
	n->len	     = skb->len;

	if (skb_shinfo(skb)->nr_frags) {
		int i;

		if (skb_orphan_frags(skb, gfp_mask) ||
		    skb_zerocopy_clone(n, skb, gfp_mask)) {
			kfree_skb(n);
			n = NULL;
			goto out;
		}
		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			skb_shinfo(n)->frags[i] = skb_shinfo(skb)->frags[i];
			skb_frag_ref(skb, i);
		}
		skb_shinfo(n)->nr_frags = i;
	}

	if (skb_has_frag_list(skb)) {
		skb_shinfo(n)->frag_list = skb_shinfo(skb)->frag_list;
		skb_clone_fraglist(n);
	}

	skb_copy_header(n, skb);
out:
	return n;
}