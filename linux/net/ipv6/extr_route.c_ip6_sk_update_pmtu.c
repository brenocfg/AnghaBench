#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_bound_dev_if; int /*<<< orphan*/  sk_v6_daddr; int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_mark; } ;
struct sk_buff {scalar_t__ dev; } ;
struct dst_entry {TYPE_1__* ops; int /*<<< orphan*/  obsolete; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  dst_cookie; } ;
struct TYPE_3__ {scalar_t__ (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_datagram_dst_update (struct sock*,int) ; 
 int /*<<< orphan*/  ip6_update_pmtu (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_v4mapped (int /*<<< orphan*/ *) ; 
 int l3mdev_master_ifindex (scalar_t__) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 scalar_t__ stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

void ip6_sk_update_pmtu(struct sk_buff *skb, struct sock *sk, __be32 mtu)
{
	int oif = sk->sk_bound_dev_if;
	struct dst_entry *dst;

	if (!oif && skb->dev)
		oif = l3mdev_master_ifindex(skb->dev);

	ip6_update_pmtu(skb, sock_net(sk), mtu, oif, sk->sk_mark, sk->sk_uid);

	dst = __sk_dst_get(sk);
	if (!dst || !dst->obsolete ||
	    dst->ops->check(dst, inet6_sk(sk)->dst_cookie))
		return;

	bh_lock_sock(sk);
	if (!sock_owned_by_user(sk) && !ipv6_addr_v4mapped(&sk->sk_v6_daddr))
		ip6_datagram_dst_update(sk, false);
	bh_unlock_sock(sk);
}