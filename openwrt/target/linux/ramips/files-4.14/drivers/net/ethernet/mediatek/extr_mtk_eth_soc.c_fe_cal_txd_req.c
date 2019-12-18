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
struct skb_frag_struct {int size; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int TX_DMA_BUF_LEN ; 
 struct sk_buff* fe_next_frag (struct sk_buff*,struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline int fe_cal_txd_req(struct sk_buff *skb)
{
	struct sk_buff *head = skb;
	int i, nfrags = 0;
	struct skb_frag_struct *frag;

next_frag:
	nfrags++;
	if (skb_is_gso(skb)) {
		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			frag = &skb_shinfo(skb)->frags[i];
			nfrags += DIV_ROUND_UP(frag->size, TX_DMA_BUF_LEN);
		}
	} else {
		nfrags += skb_shinfo(skb)->nr_frags;
	}

	skb = fe_next_frag(head, skb);
	if (skb)
		goto next_frag;

	return DIV_ROUND_UP(nfrags, 2);
}