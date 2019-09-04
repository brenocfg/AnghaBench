#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {unsigned long expires; } ;
struct xfrm_policy_queue {unsigned long timeout; TYPE_3__ hold_queue; TYPE_1__ hold_timer; } ;
struct xfrm_policy {struct xfrm_policy_queue polq; } ;
struct xfrm_dst {struct xfrm_policy** pols; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ XFRM_MAX_QUEUE_LEN ; 
 unsigned long XFRM_QUEUE_TMO_MIN ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_3__*,struct sk_buff*) ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fclone_busy (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 

__attribute__((used)) static int xdst_queue_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	unsigned long sched_next;
	struct dst_entry *dst = skb_dst(skb);
	struct xfrm_dst *xdst = (struct xfrm_dst *) dst;
	struct xfrm_policy *pol = xdst->pols[0];
	struct xfrm_policy_queue *pq = &pol->polq;

	if (unlikely(skb_fclone_busy(sk, skb))) {
		kfree_skb(skb);
		return 0;
	}

	if (pq->hold_queue.qlen > XFRM_MAX_QUEUE_LEN) {
		kfree_skb(skb);
		return -EAGAIN;
	}

	skb_dst_force(skb);

	spin_lock_bh(&pq->hold_queue.lock);

	if (!pq->timeout)
		pq->timeout = XFRM_QUEUE_TMO_MIN;

	sched_next = jiffies + pq->timeout;

	if (del_timer(&pq->hold_timer)) {
		if (time_before(pq->hold_timer.expires, sched_next))
			sched_next = pq->hold_timer.expires;
		xfrm_pol_put(pol);
	}

	__skb_queue_tail(&pq->hold_queue, skb);
	if (!mod_timer(&pq->hold_timer, sched_next))
		xfrm_pol_hold(pol);

	spin_unlock_bh(&pq->hold_queue.lock);

	return 0;
}