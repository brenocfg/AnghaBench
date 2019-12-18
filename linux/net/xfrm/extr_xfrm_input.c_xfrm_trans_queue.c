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
struct xfrm_trans_tasklet {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int (* finish ) (struct net*,struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 int ENOBUFS ; 
 TYPE_1__* XFRM_TRANS_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ netdev_max_backlog ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct xfrm_trans_tasklet* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_trans_tasklet ; 

int xfrm_trans_queue(struct sk_buff *skb,
		     int (*finish)(struct net *, struct sock *,
				   struct sk_buff *))
{
	struct xfrm_trans_tasklet *trans;

	trans = this_cpu_ptr(&xfrm_trans_tasklet);

	if (skb_queue_len(&trans->queue) >= netdev_max_backlog)
		return -ENOBUFS;

	XFRM_TRANS_SKB_CB(skb)->finish = finish;
	__skb_queue_tail(&trans->queue, skb);
	tasklet_schedule(&trans->tasklet);
	return 0;
}