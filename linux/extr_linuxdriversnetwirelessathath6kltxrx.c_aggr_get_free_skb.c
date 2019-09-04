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
struct sk_buff {int dummy; } ;
struct aggr_info {int /*<<< orphan*/  rx_amsdu_freeq; } ;

/* Variables and functions */
 int AGGR_NUM_OF_FREE_NETBUFS ; 
 int /*<<< orphan*/  ath6kl_alloc_netbufs (int /*<<< orphan*/ *,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *aggr_get_free_skb(struct aggr_info *p_aggr)
{
	struct sk_buff *skb = NULL;

	if (skb_queue_len(&p_aggr->rx_amsdu_freeq) <
	    (AGGR_NUM_OF_FREE_NETBUFS >> 2))
		ath6kl_alloc_netbufs(&p_aggr->rx_amsdu_freeq,
				     AGGR_NUM_OF_FREE_NETBUFS);

	skb = skb_dequeue(&p_aggr->rx_amsdu_freeq);

	return skb;
}