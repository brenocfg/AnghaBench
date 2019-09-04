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
typedef  size_t u8 ;
struct skb_shared_info {size_t nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  truesize; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct cxgbit_sock {struct sk_buff* lro_hskb; } ;

/* Variables and functions */
 int /*<<< orphan*/  LRO_SKB_MIN_HEADROOM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void cxgbit_lro_hskb_reset(struct cxgbit_sock *csk)
{
	struct sk_buff *skb = csk->lro_hskb;
	struct skb_shared_info *ssi = skb_shinfo(skb);
	u8 i;

	memset(skb->data, 0, LRO_SKB_MIN_HEADROOM);
	for (i = 0; i < ssi->nr_frags; i++)
		put_page(skb_frag_page(&ssi->frags[i]));
	ssi->nr_frags = 0;
	skb->data_len = 0;
	skb->truesize -= skb->len;
	skb->len = 0;
}