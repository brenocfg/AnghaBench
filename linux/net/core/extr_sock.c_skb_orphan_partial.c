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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {int /*<<< orphan*/  destructor; int /*<<< orphan*/  truesize; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ can_skb_orphan_partial (struct sk_buff*) ; 
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_sub_and_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_is_tcp_pure_ack (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_efree ; 

void skb_orphan_partial(struct sk_buff *skb)
{
	if (skb_is_tcp_pure_ack(skb))
		return;

	if (can_skb_orphan_partial(skb)) {
		struct sock *sk = skb->sk;

		if (refcount_inc_not_zero(&sk->sk_refcnt)) {
			WARN_ON(refcount_sub_and_test(skb->truesize, &sk->sk_wmem_alloc));
			skb->destructor = sock_efree;
		}
	} else {
		skb_orphan(skb);
	}
}