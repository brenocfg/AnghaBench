#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_err; struct sk_buff_head sk_error_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ee_origin; } ;
struct TYPE_4__ {TYPE_1__ ee; } ;

/* Variables and functions */
 TYPE_2__* SKB_EXT_ERR (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int is_icmp_err_skb (struct sk_buff*) ; 
 struct sk_buff* skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

struct sk_buff *sock_dequeue_err_skb(struct sock *sk)
{
	struct sk_buff_head *q = &sk->sk_error_queue;
	struct sk_buff *skb, *skb_next = NULL;
	bool icmp_next = false;
	unsigned long flags;

	spin_lock_irqsave(&q->lock, flags);
	skb = __skb_dequeue(q);
	if (skb && (skb_next = skb_peek(q))) {
		icmp_next = is_icmp_err_skb(skb_next);
		if (icmp_next)
			sk->sk_err = SKB_EXT_ERR(skb_next)->ee.ee_origin;
	}
	spin_unlock_irqrestore(&q->lock, flags);

	if (is_icmp_err_skb(skb) && !icmp_next)
		sk->sk_err = 0;

	if (skb_next)
		sk->sk_error_report(sk);

	return skb;
}