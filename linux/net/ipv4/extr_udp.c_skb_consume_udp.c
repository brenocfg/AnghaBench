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
struct sock {int /*<<< orphan*/  sk_peek_off; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __consume_stateless_skb (struct sk_buff*) ; 
 int lock_sock_fast (struct sock*) ; 
 int /*<<< orphan*/  sk_peek_offset_bwd (struct sock*,int) ; 
 int /*<<< orphan*/  skb_release_head_state (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unref (struct sk_buff*) ; 
 int udp_skb_has_head_state (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_sock_fast (struct sock*,int) ; 

void skb_consume_udp(struct sock *sk, struct sk_buff *skb, int len)
{
	if (unlikely(READ_ONCE(sk->sk_peek_off) >= 0)) {
		bool slow = lock_sock_fast(sk);

		sk_peek_offset_bwd(sk, len);
		unlock_sock_fast(sk, slow);
	}

	if (!skb_unref(skb))
		return;

	/* In the more common cases we cleared the head states previously,
	 * see __udp_queue_rcv_skb().
	 */
	if (unlikely(udp_skb_has_head_state(skb)))
		skb_release_head_state(skb);
	__consume_stateless_skb(skb);
}