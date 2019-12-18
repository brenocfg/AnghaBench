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
struct xfrm_trans_tasklet {int /*<<< orphan*/  queue; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* finish ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ;} ;

/* Variables and functions */
 TYPE_1__* XFRM_TRANS_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_splice_init (int /*<<< orphan*/ *,struct sk_buff_head*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void xfrm_trans_reinject(unsigned long data)
{
	struct xfrm_trans_tasklet *trans = (void *)data;
	struct sk_buff_head queue;
	struct sk_buff *skb;

	__skb_queue_head_init(&queue);
	skb_queue_splice_init(&trans->queue, &queue);

	while ((skb = __skb_dequeue(&queue)))
		XFRM_TRANS_SKB_CB(skb)->finish(dev_net(skb->dev), NULL, skb);
}