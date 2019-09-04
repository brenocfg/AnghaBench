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
struct sockaddr_l2tpip6 {scalar_t__ l2tp_family; int l2tp_scope_id; int /*<<< orphan*/  l2tp_conn_id; int /*<<< orphan*/  l2tp_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; int sk_bound_dev_if; int /*<<< orphan*/  sk_v6_rcv_saddr; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  saddr; } ;
struct inet_sock {void* inet_rcv_saddr; void* inet_saddr; } ;
typedef  void* __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  conn_id; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MAPPED ; 
 int IPV6_ADDR_MULTICAST ; 
 void* LOOPBACK4_IPV6 ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ __l2tp_ip6_bind_lookup (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_chk_addr (struct net*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_ip6_bind_table ; 
 int /*<<< orphan*/  l2tp_ip6_lock ; 
 TYPE_1__* l2tp_ip6_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_ip6_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sockaddr_l2tpip6 *addr = (struct sockaddr_l2tpip6 *) uaddr;
	struct net *net = sock_net(sk);
	__be32 v4addr = 0;
	int bound_dev_if;
	int addr_type;
	int err;

	if (addr->l2tp_family != AF_INET6)
		return -EINVAL;
	if (addr_len < sizeof(*addr))
		return -EINVAL;

	addr_type = ipv6_addr_type(&addr->l2tp_addr);

	/* l2tp_ip6 sockets are IPv6 only */
	if (addr_type == IPV6_ADDR_MAPPED)
		return -EADDRNOTAVAIL;

	/* L2TP is point-point, not multicast */
	if (addr_type & IPV6_ADDR_MULTICAST)
		return -EADDRNOTAVAIL;

	lock_sock(sk);

	err = -EINVAL;
	if (!sock_flag(sk, SOCK_ZAPPED))
		goto out_unlock;

	if (sk->sk_state != TCP_CLOSE)
		goto out_unlock;

	bound_dev_if = sk->sk_bound_dev_if;

	/* Check if the address belongs to the host. */
	rcu_read_lock();
	if (addr_type != IPV6_ADDR_ANY) {
		struct net_device *dev = NULL;

		if (addr_type & IPV6_ADDR_LINKLOCAL) {
			if (addr->l2tp_scope_id)
				bound_dev_if = addr->l2tp_scope_id;

			/* Binding to link-local address requires an
			 * interface.
			 */
			if (!bound_dev_if)
				goto out_unlock_rcu;

			err = -ENODEV;
			dev = dev_get_by_index_rcu(sock_net(sk), bound_dev_if);
			if (!dev)
				goto out_unlock_rcu;
		}

		/* ipv4 addr of the socket is invalid.  Only the
		 * unspecified and mapped address have a v4 equivalent.
		 */
		v4addr = LOOPBACK4_IPV6;
		err = -EADDRNOTAVAIL;
		if (!ipv6_chk_addr(sock_net(sk), &addr->l2tp_addr, dev, 0))
			goto out_unlock_rcu;
	}
	rcu_read_unlock();

	write_lock_bh(&l2tp_ip6_lock);
	if (__l2tp_ip6_bind_lookup(net, &addr->l2tp_addr, NULL, bound_dev_if,
				   addr->l2tp_conn_id)) {
		write_unlock_bh(&l2tp_ip6_lock);
		err = -EADDRINUSE;
		goto out_unlock;
	}

	inet->inet_saddr = v4addr;
	inet->inet_rcv_saddr = v4addr;
	sk->sk_bound_dev_if = bound_dev_if;
	sk->sk_v6_rcv_saddr = addr->l2tp_addr;
	np->saddr = addr->l2tp_addr;

	l2tp_ip6_sk(sk)->conn_id = addr->l2tp_conn_id;

	sk_add_bind_node(sk, &l2tp_ip6_bind_table);
	sk_del_node_init(sk);
	write_unlock_bh(&l2tp_ip6_lock);

	sock_reset_flag(sk, SOCK_ZAPPED);
	release_sock(sk);
	return 0;

out_unlock_rcu:
	rcu_read_unlock();
out_unlock:
	release_sock(sk);

	return err;
}