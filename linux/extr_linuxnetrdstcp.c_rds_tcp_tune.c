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
struct sock {scalar_t__ sk_sndbuf; int /*<<< orphan*/  sk_userlocks; } ;
struct rds_tcp_net {scalar_t__ sndbuf_size; scalar_t__ rcvbuf_size; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_RCVBUF_LOCK ; 
 int /*<<< orphan*/  SOCK_SNDBUF_LOCK ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct rds_tcp_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_netid ; 
 int /*<<< orphan*/  rds_tcp_nonagle (struct socket*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 

void rds_tcp_tune(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct rds_tcp_net *rtn = net_generic(net, rds_tcp_netid);

	rds_tcp_nonagle(sock);
	lock_sock(sk);
	if (rtn->sndbuf_size > 0) {
		sk->sk_sndbuf = rtn->sndbuf_size;
		sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
	}
	if (rtn->rcvbuf_size > 0) {
		sk->sk_sndbuf = rtn->rcvbuf_size;
		sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
	}
	release_sock(sk);
}