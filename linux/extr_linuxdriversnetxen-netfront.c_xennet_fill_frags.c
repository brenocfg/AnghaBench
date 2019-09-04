#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xen_netif_rx_response {int /*<<< orphan*/  status; int /*<<< orphan*/  offset; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {unsigned int rsp_cons; } ;
struct netfront_queue {TYPE_2__ rx; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_6__ {unsigned int pull_to; } ;
struct TYPE_4__ {scalar_t__ nr_frags; int /*<<< orphan*/ * frags; } ;
typedef  unsigned int RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 TYPE_3__* NETFRONT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct xen_netif_rx_response* RING_GET_RESPONSE (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,unsigned int) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static RING_IDX xennet_fill_frags(struct netfront_queue *queue,
				  struct sk_buff *skb,
				  struct sk_buff_head *list)
{
	RING_IDX cons = queue->rx.rsp_cons;
	struct sk_buff *nskb;

	while ((nskb = __skb_dequeue(list))) {
		struct xen_netif_rx_response *rx =
			RING_GET_RESPONSE(&queue->rx, ++cons);
		skb_frag_t *nfrag = &skb_shinfo(nskb)->frags[0];

		if (skb_shinfo(skb)->nr_frags == MAX_SKB_FRAGS) {
			unsigned int pull_to = NETFRONT_SKB_CB(skb)->pull_to;

			BUG_ON(pull_to < skb_headlen(skb));
			__pskb_pull_tail(skb, pull_to - skb_headlen(skb));
		}
		if (unlikely(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS)) {
			queue->rx.rsp_cons = ++cons;
			kfree_skb(nskb);
			return ~0U;
		}

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				skb_frag_page(nfrag),
				rx->offset, rx->status, PAGE_SIZE);

		skb_shinfo(nskb)->nr_frags = 0;
		kfree_skb(nskb);
	}

	return cons;
}