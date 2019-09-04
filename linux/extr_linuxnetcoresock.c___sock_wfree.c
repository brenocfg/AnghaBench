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
struct sk_buff {int /*<<< orphan*/  truesize; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_free (struct sock*) ; 
 scalar_t__ refcount_sub_and_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __sock_wfree(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;

	if (refcount_sub_and_test(skb->truesize, &sk->sk_wmem_alloc))
		__sk_free(sk);
}