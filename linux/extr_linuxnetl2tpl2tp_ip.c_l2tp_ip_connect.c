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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_l2tpip {int /*<<< orphan*/  l2tp_conn_id; TYPE_1__ l2tp_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_bind_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  peer_conn_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int __ip4_datagram_connect (struct sock*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_ip_bind_table ; 
 int /*<<< orphan*/  l2tp_ip_lock ; 
 TYPE_2__* l2tp_ip_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_ip_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct sockaddr_l2tpip *lsa = (struct sockaddr_l2tpip *) uaddr;
	int rc;

	if (addr_len < sizeof(*lsa))
		return -EINVAL;

	if (ipv4_is_multicast(lsa->l2tp_addr.s_addr))
		return -EINVAL;

	lock_sock(sk);

	/* Must bind first - autobinding does not work */
	if (sock_flag(sk, SOCK_ZAPPED)) {
		rc = -EINVAL;
		goto out_sk;
	}

	rc = __ip4_datagram_connect(sk, uaddr, addr_len);
	if (rc < 0)
		goto out_sk;

	l2tp_ip_sk(sk)->peer_conn_id = lsa->l2tp_conn_id;

	write_lock_bh(&l2tp_ip_lock);
	hlist_del_init(&sk->sk_bind_node);
	sk_add_bind_node(sk, &l2tp_ip_bind_table);
	write_unlock_bh(&l2tp_ip_lock);

out_sk:
	release_sock(sk);

	return rc;
}