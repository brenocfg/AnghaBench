#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct xfrm_policy_queue {TYPE_1__ hold_queue; int /*<<< orphan*/  hold_timer; int /*<<< orphan*/  timeout; } ;
struct xfrm_policy {struct xfrm_policy_queue polq; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_QUEUE_TMO_MIN ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_splice (struct sk_buff_head*,TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (TYPE_1__*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 

__attribute__((used)) static void xfrm_policy_requeue(struct xfrm_policy *old,
				struct xfrm_policy *new)
{
	struct xfrm_policy_queue *pq = &old->polq;
	struct sk_buff_head list;

	if (skb_queue_empty(&pq->hold_queue))
		return;

	__skb_queue_head_init(&list);

	spin_lock_bh(&pq->hold_queue.lock);
	skb_queue_splice_init(&pq->hold_queue, &list);
	if (del_timer(&pq->hold_timer))
		xfrm_pol_put(old);
	spin_unlock_bh(&pq->hold_queue.lock);

	pq = &new->polq;

	spin_lock_bh(&pq->hold_queue.lock);
	skb_queue_splice(&list, &pq->hold_queue);
	pq->timeout = XFRM_QUEUE_TMO_MIN;
	if (!mod_timer(&pq->hold_timer, jiffies))
		xfrm_pol_hold(new);
	spin_unlock_bh(&pq->hold_queue.lock);
}