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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  destructor; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash_from_sk (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_edemux ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_wfree ; 
 scalar_t__ unlikely (int) ; 

void skb_set_owner_w(struct sk_buff *skb, struct sock *sk)
{
	skb_orphan(skb);
	skb->sk = sk;
#ifdef CONFIG_INET
	if (unlikely(!sk_fullsock(sk))) {
		skb->destructor = sock_edemux;
		sock_hold(sk);
		return;
	}
#endif
	skb->destructor = sock_wfree;
	skb_set_hash_from_sk(skb, sk);
	/*
	 * We used to take a refcount on sk, but following operation
	 * is enough to guarantee sk_free() wont free this sock until
	 * all in-flight packets are completed
	 */
	refcount_add(skb->truesize, &sk->sk_wmem_alloc);
}