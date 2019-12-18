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
typedef  int u32 ;
struct sk_buff {int len; int data_len; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_frag_off_add (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  skb_frag_ref (struct sk_buff*,int) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  skb_frag_size_sub (int /*<<< orphan*/ *,int const) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline void skb_split_no_header(struct sk_buff *skb,
				       struct sk_buff* skb1,
				       const u32 len, int pos)
{
	int i, k = 0;
	const int nfrags = skb_shinfo(skb)->nr_frags;

	skb_shinfo(skb)->nr_frags = 0;
	skb1->len		  = skb1->data_len = skb->len - len;
	skb->len		  = len;
	skb->data_len		  = len - pos;

	for (i = 0; i < nfrags; i++) {
		int size = skb_frag_size(&skb_shinfo(skb)->frags[i]);

		if (pos + size > len) {
			skb_shinfo(skb1)->frags[k] = skb_shinfo(skb)->frags[i];

			if (pos < len) {
				/* Split frag.
				 * We have two variants in this case:
				 * 1. Move all the frag to the second
				 *    part, if it is possible. F.e.
				 *    this approach is mandatory for TUX,
				 *    where splitting is expensive.
				 * 2. Split is accurately. We make this.
				 */
				skb_frag_ref(skb, i);
				skb_frag_off_add(&skb_shinfo(skb1)->frags[0], len - pos);
				skb_frag_size_sub(&skb_shinfo(skb1)->frags[0], len - pos);
				skb_frag_size_set(&skb_shinfo(skb)->frags[i], len - pos);
				skb_shinfo(skb)->nr_frags++;
			}
			k++;
		} else
			skb_shinfo(skb)->nr_frags++;
		pos += size;
	}
	skb_shinfo(skb1)->nr_frags = k;
}