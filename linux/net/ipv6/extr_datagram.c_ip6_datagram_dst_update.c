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
struct sock {TYPE_1__* sk_prot; int /*<<< orphan*/  sk_v6_rcv_saddr; } ;
struct ipv6_txoptions {int dummy; } ;
struct ipv6_pinfo {int flow_label; int /*<<< orphan*/  saddr; int /*<<< orphan*/  opt; scalar_t__ sndflow; } ;
struct ip6_flowlabel {struct ipv6_txoptions* opt; } ;
struct inet_sock {int /*<<< orphan*/  inet_rcv_saddr; } ;
struct in6_addr {int dummy; } ;
struct flowi6 {int /*<<< orphan*/  saddr; } ;
struct dst_entry {struct ipv6_txoptions* opt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rehash ) (struct sock*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int IPV6_FLOWLABEL_MASK ; 
 scalar_t__ IS_ERR (struct ip6_flowlabel*) ; 
 int /*<<< orphan*/  LOOPBACK4_IPV6 ; 
 int PTR_ERR (struct ip6_flowlabel*) ; 
 struct ip6_flowlabel* fl6_sock_lookup (struct sock*,int) ; 
 int /*<<< orphan*/  fl6_sock_release (struct ip6_flowlabel*) ; 
 struct in6_addr* fl6_update_dst (struct flowi6*,struct ipv6_txoptions*,struct in6_addr*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_datagram_flow_key_init (struct flowi6*,struct sock*) ; 
 struct ip6_flowlabel* ip6_dst_lookup_flow (struct sock*,struct flowi6*,struct in6_addr*) ; 
 int /*<<< orphan*/  ip6_sk_dst_store_flow (struct sock*,struct ip6_flowlabel*,struct flowi6*) ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 struct ipv6_txoptions* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int ip6_datagram_dst_update(struct sock *sk, bool fix_sk_saddr)
{
	struct ip6_flowlabel *flowlabel = NULL;
	struct in6_addr *final_p, final;
	struct ipv6_txoptions *opt;
	struct dst_entry *dst;
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct flowi6 fl6;
	int err = 0;

	if (np->sndflow && (np->flow_label & IPV6_FLOWLABEL_MASK)) {
		flowlabel = fl6_sock_lookup(sk, np->flow_label);
		if (IS_ERR(flowlabel))
			return -EINVAL;
	}
	ip6_datagram_flow_key_init(&fl6, sk);

	rcu_read_lock();
	opt = flowlabel ? flowlabel->opt : rcu_dereference(np->opt);
	final_p = fl6_update_dst(&fl6, opt, &final);
	rcu_read_unlock();

	dst = ip6_dst_lookup_flow(sk, &fl6, final_p);
	if (IS_ERR(dst)) {
		err = PTR_ERR(dst);
		goto out;
	}

	if (fix_sk_saddr) {
		if (ipv6_addr_any(&np->saddr))
			np->saddr = fl6.saddr;

		if (ipv6_addr_any(&sk->sk_v6_rcv_saddr)) {
			sk->sk_v6_rcv_saddr = fl6.saddr;
			inet->inet_rcv_saddr = LOOPBACK4_IPV6;
			if (sk->sk_prot->rehash)
				sk->sk_prot->rehash(sk);
		}
	}

	ip6_sk_dst_store_flow(sk, dst, &fl6);

out:
	fl6_sock_release(flowlabel);
	return err;
}