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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int lock_sock_fast (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_reclaim_partial (struct sock*) ; 
 int /*<<< orphan*/  sk_peek_offset_bwd (struct sock*,int) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unref (struct sk_buff*) ; 
 int /*<<< orphan*/  unlock_sock_fast (struct sock*,int) ; 

void __skb_free_datagram_locked(struct sock *sk, struct sk_buff *skb, int len)
{
	bool slow;

	if (!skb_unref(skb)) {
		sk_peek_offset_bwd(sk, len);
		return;
	}

	slow = lock_sock_fast(sk);
	sk_peek_offset_bwd(sk, len);
	skb_orphan(skb);
	sk_mem_reclaim_partial(sk);
	unlock_sock_fast(sk, slow);

	/* skb is now orphaned, can be freed outside of locked section */
	__kfree_skb(skb);
}