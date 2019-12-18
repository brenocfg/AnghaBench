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
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_l2tpip {scalar_t__ l2tp_family; int /*<<< orphan*/  l2tp_conn_id; TYPE_1__ l2tp_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct net {int dummy; } ;
struct inet_sock {scalar_t__ inet_saddr; scalar_t__ inet_rcv_saddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  conn_id; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int RTN_BROADCAST ; 
 int RTN_LOCAL ; 
 int RTN_MULTICAST ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ __l2tp_ip_bind_lookup (struct net*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inet_addr_type (struct net*,scalar_t__) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  l2tp_ip_bind_table ; 
 int /*<<< orphan*/  l2tp_ip_lock ; 
 TYPE_2__* l2tp_ip_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_ip_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct inet_sock *inet = inet_sk(sk);
	struct sockaddr_l2tpip *addr = (struct sockaddr_l2tpip *) uaddr;
	struct net *net = sock_net(sk);
	int ret;
	int chk_addr_ret;

	if (addr_len < sizeof(struct sockaddr_l2tpip))
		return -EINVAL;
	if (addr->l2tp_family != AF_INET)
		return -EINVAL;

	lock_sock(sk);

	ret = -EINVAL;
	if (!sock_flag(sk, SOCK_ZAPPED))
		goto out;

	if (sk->sk_state != TCP_CLOSE)
		goto out;

	chk_addr_ret = inet_addr_type(net, addr->l2tp_addr.s_addr);
	ret = -EADDRNOTAVAIL;
	if (addr->l2tp_addr.s_addr && chk_addr_ret != RTN_LOCAL &&
	    chk_addr_ret != RTN_MULTICAST && chk_addr_ret != RTN_BROADCAST)
		goto out;

	if (addr->l2tp_addr.s_addr)
		inet->inet_rcv_saddr = inet->inet_saddr = addr->l2tp_addr.s_addr;
	if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
		inet->inet_saddr = 0;  /* Use device */

	write_lock_bh(&l2tp_ip_lock);
	if (__l2tp_ip_bind_lookup(net, addr->l2tp_addr.s_addr, 0,
				  sk->sk_bound_dev_if, addr->l2tp_conn_id)) {
		write_unlock_bh(&l2tp_ip_lock);
		ret = -EADDRINUSE;
		goto out;
	}

	sk_dst_reset(sk);
	l2tp_ip_sk(sk)->conn_id = addr->l2tp_conn_id;

	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	sk_del_node_init(sk);
	write_unlock_bh(&l2tp_ip_lock);

	ret = 0;
	sock_reset_flag(sk, SOCK_ZAPPED);

out:
	release_sock(sk);

	return ret;
}