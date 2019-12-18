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
struct sockaddr_l2tpip6 {int /*<<< orphan*/  l2tp_conn_id; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; struct in6_addr sin6_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_bind_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_conn_id; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_MULTICAST ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int __ip6_datagram_connect (struct sock*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (struct in6_addr*) ; 
 int /*<<< orphan*/  l2tp_ip6_bind_table ; 
 int /*<<< orphan*/  l2tp_ip6_lock ; 
 TYPE_1__* l2tp_ip6_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_ip6_connect(struct sock *sk, struct sockaddr *uaddr,
			    int addr_len)
{
	struct sockaddr_l2tpip6 *lsa = (struct sockaddr_l2tpip6 *) uaddr;
	struct sockaddr_in6	*usin = (struct sockaddr_in6 *) uaddr;
	struct in6_addr	*daddr;
	int	addr_type;
	int rc;

	if (addr_len < sizeof(*lsa))
		return -EINVAL;

	if (usin->sin6_family != AF_INET6)
		return -EINVAL;

	addr_type = ipv6_addr_type(&usin->sin6_addr);
	if (addr_type & IPV6_ADDR_MULTICAST)
		return -EINVAL;

	if (addr_type & IPV6_ADDR_MAPPED) {
		daddr = &usin->sin6_addr;
		if (ipv4_is_multicast(daddr->s6_addr32[3]))
			return -EINVAL;
	}

	lock_sock(sk);

	 /* Must bind first - autobinding does not work */
	if (sock_flag(sk, SOCK_ZAPPED)) {
		rc = -EINVAL;
		goto out_sk;
	}

	rc = __ip6_datagram_connect(sk, uaddr, addr_len);
	if (rc < 0)
		goto out_sk;

	l2tp_ip6_sk(sk)->peer_conn_id = lsa->l2tp_conn_id;

	write_lock_bh(&l2tp_ip6_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &l2tp_ip6_bind_table);
	write_unlock_bh(&l2tp_ip6_lock);

out_sk:
	release_sock(sk);

	return rc;
}