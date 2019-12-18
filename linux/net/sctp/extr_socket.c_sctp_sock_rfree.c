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
struct sock {int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {struct sock* sk; } ;
struct sctp_ulpevent {int /*<<< orphan*/  rmem_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int /*<<< orphan*/ ) ; 

void sctp_sock_rfree(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	struct sctp_ulpevent *event = sctp_skb2event(skb);

	atomic_sub(event->rmem_len, &sk->sk_rmem_alloc);

	/*
	 * Mimic the behavior of sock_rfree
	 */
	sk_mem_uncharge(sk, event->rmem_len);
}