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
struct sock {int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_redirect (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

void ip6_sk_redirect(struct sk_buff *skb, struct sock *sk)
{
	ip6_redirect(skb, sock_net(sk), sk->sk_bound_dev_if, sk->sk_mark,
		     sk->sk_uid);
}