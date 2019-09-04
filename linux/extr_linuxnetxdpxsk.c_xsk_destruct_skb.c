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
typedef  int /*<<< orphan*/  u64 ;
struct xdp_sock {int /*<<< orphan*/  tx_completion_lock; TYPE_1__* umem; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {scalar_t__ destructor_arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_wfree (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct xdp_sock* xdp_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xskq_produce_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xsk_destruct_skb(struct sk_buff *skb)
{
	u64 addr = (u64)(long)skb_shinfo(skb)->destructor_arg;
	struct xdp_sock *xs = xdp_sk(skb->sk);
	unsigned long flags;

	spin_lock_irqsave(&xs->tx_completion_lock, flags);
	WARN_ON_ONCE(xskq_produce_addr(xs->umem->cq, addr));
	spin_unlock_irqrestore(&xs->tx_completion_lock, flags);

	sock_wfree(skb);
}