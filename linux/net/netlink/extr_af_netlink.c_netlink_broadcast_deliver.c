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
struct sock {int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int dummy; } ;
struct netlink_sock {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_S_CONGESTED ; 
 int /*<<< orphan*/  __netlink_sendskb (struct sock*,struct sk_buff*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlink_broadcast_deliver(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf &&
	    !test_bit(NETLINK_S_CONGESTED, &nlk->state)) {
		netlink_skb_set_owner_r(skb, sk);
		__netlink_sendskb(sk, skb);
		return atomic_read(&sk->sk_rmem_alloc) > (sk->sk_rcvbuf >> 1);
	}
	return -1;
}