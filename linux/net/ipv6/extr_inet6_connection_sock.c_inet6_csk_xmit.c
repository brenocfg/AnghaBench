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
struct sock {int sk_err_soft; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_v6_daddr; scalar_t__ sk_route_caps; } ;
struct sk_buff {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  tclass; int /*<<< orphan*/  opt; } ;
struct flowi6 {int /*<<< orphan*/  daddr; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int PTR_ERR (struct dst_entry*) ; 
 struct dst_entry* inet6_csk_route_socket (struct sock*,struct flowi6*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int ip6_xmit (struct sock*,struct sk_buff*,struct flowi6*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_dst_set_noref (struct sk_buff*,struct dst_entry*) ; 

int inet6_csk_xmit(struct sock *sk, struct sk_buff *skb, struct flowi *fl_unused)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct flowi6 fl6;
	struct dst_entry *dst;
	int res;

	dst = inet6_csk_route_socket(sk, &fl6);
	if (IS_ERR(dst)) {
		sk->sk_err_soft = -PTR_ERR(dst);
		sk->sk_route_caps = 0;
		kfree_skb(skb);
		return PTR_ERR(dst);
	}

	rcu_read_lock();
	skb_dst_set_noref(skb, dst);

	/* Restore final destination back after routing done */
	fl6.daddr = sk->sk_v6_daddr;

	res = ip6_xmit(sk, skb, &fl6, sk->sk_mark, rcu_dereference(np->opt),
		       np->tclass,  sk->sk_priority);
	rcu_read_unlock();
	return res;
}