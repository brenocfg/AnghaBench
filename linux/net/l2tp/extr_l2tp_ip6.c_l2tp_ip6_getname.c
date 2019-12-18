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
struct socket {struct sock* sk; } ;
struct sockaddr_l2tpip6 {scalar_t__ l2tp_scope_id; int /*<<< orphan*/  l2tp_addr; scalar_t__ l2tp_conn_id; scalar_t__ l2tp_flowinfo; scalar_t__ l2tp_unused; int /*<<< orphan*/  l2tp_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_bound_dev_if; int /*<<< orphan*/  sk_v6_rcv_saddr; int /*<<< orphan*/  sk_v6_daddr; } ;
struct l2tp_ip6_sock {scalar_t__ conn_id; scalar_t__ peer_conn_id; } ;
struct ipv6_pinfo {int /*<<< orphan*/  saddr; scalar_t__ flow_label; scalar_t__ sndflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOTCONN ; 
 int IPV6_ADDR_LINKLOCAL ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 struct l2tp_ip6_sock* l2tp_ip6_sk (struct sock*) ; 

__attribute__((used)) static int l2tp_ip6_getname(struct socket *sock, struct sockaddr *uaddr,
			    int peer)
{
	struct sockaddr_l2tpip6 *lsa = (struct sockaddr_l2tpip6 *)uaddr;
	struct sock *sk = sock->sk;
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct l2tp_ip6_sock *lsk = l2tp_ip6_sk(sk);

	lsa->l2tp_family = AF_INET6;
	lsa->l2tp_flowinfo = 0;
	lsa->l2tp_scope_id = 0;
	lsa->l2tp_unused = 0;
	if (peer) {
		if (!lsk->peer_conn_id)
			return -ENOTCONN;
		lsa->l2tp_conn_id = lsk->peer_conn_id;
		lsa->l2tp_addr = sk->sk_v6_daddr;
		if (np->sndflow)
			lsa->l2tp_flowinfo = np->flow_label;
	} else {
		if (ipv6_addr_any(&sk->sk_v6_rcv_saddr))
			lsa->l2tp_addr = np->saddr;
		else
			lsa->l2tp_addr = sk->sk_v6_rcv_saddr;

		lsa->l2tp_conn_id = lsk->conn_id;
	}
	if (ipv6_addr_type(&lsa->l2tp_addr) & IPV6_ADDR_LINKLOCAL)
		lsa->l2tp_scope_id = sk->sk_bound_dev_if;
	return sizeof(*lsa);
}