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
struct sock {int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  sk_filter; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ checksum; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_1__* raw6_sk (struct sock*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_checksum_complete (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static inline int rawv6_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	if ((raw6_sk(sk)->checksum || rcu_access_pointer(sk->sk_filter)) &&
	    skb_checksum_complete(skb)) {
		atomic_inc(&sk->sk_drops);
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	/* Charge it to the socket. */
	skb_dst_drop(skb);
	if (sock_queue_rcv_skb(sk, skb) < 0) {
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	return 0;
}