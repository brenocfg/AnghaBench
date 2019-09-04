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
struct sock {int /*<<< orphan*/  sk_refcnt; } ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_TSTAMP_SND ; 
 int /*<<< orphan*/  __skb_complete_tx_timestamp (struct sk_buff*,struct sock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_may_tx_timestamp (struct sock*,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void skb_complete_tx_timestamp(struct sk_buff *skb,
			       struct skb_shared_hwtstamps *hwtstamps)
{
	struct sock *sk = skb->sk;

	if (!skb_may_tx_timestamp(sk, false))
		goto err;

	/* Take a reference to prevent skb_orphan() from freeing the socket,
	 * but only if the socket refcount is not zero.
	 */
	if (likely(refcount_inc_not_zero(&sk->sk_refcnt))) {
		*skb_hwtstamps(skb) = *hwtstamps;
		__skb_complete_tx_timestamp(skb, sk, SCM_TSTAMP_SND, false);
		sock_put(sk);
		return;
	}

err:
	kfree_skb(skb);
}