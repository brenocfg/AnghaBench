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
struct sk_buff {int /*<<< orphan*/  destructor; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_efree ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

struct sk_buff *skb_clone_sk(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	struct sk_buff *clone;

	if (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		return NULL;

	clone = skb_clone(skb, GFP_ATOMIC);
	if (!clone) {
		sock_put(sk);
		return NULL;
	}

	clone->sk = sk;
	clone->destructor = sock_efree;

	return clone;
}