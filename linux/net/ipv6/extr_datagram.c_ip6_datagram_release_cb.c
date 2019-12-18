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
struct sock {int /*<<< orphan*/  sk_v6_daddr; } ;
struct dst_entry {TYPE_1__* ops; int /*<<< orphan*/  obsolete; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_cookie; } ;
struct TYPE_3__ {scalar_t__ (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 TYPE_2__* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_datagram_dst_update (struct sock*,int) ; 
 scalar_t__ ipv6_addr_v4mapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

void ip6_datagram_release_cb(struct sock *sk)
{
	struct dst_entry *dst;

	if (ipv6_addr_v4mapped(&sk->sk_v6_daddr))
		return;

	rcu_read_lock();
	dst = __sk_dst_get(sk);
	if (!dst || !dst->obsolete ||
	    dst->ops->check(dst, inet6_sk(sk)->dst_cookie)) {
		rcu_read_unlock();
		return;
	}
	rcu_read_unlock();

	ip6_datagram_dst_update(sk, false);
}