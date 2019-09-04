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
struct xdp_sock {int /*<<< orphan*/ * dev; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_prot; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 

__attribute__((used)) static int xsk_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);
	struct net *net;

	if (!sk)
		return 0;

	net = sock_net(sk);

	local_bh_disable();
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	local_bh_enable();

	if (xs->dev) {
		/* Wait for driver to stop using the xdp socket. */
		synchronize_net();
		dev_put(xs->dev);
		xs->dev = NULL;
	}

	sock_orphan(sk);
	sock->sk = NULL;

	sk_refcnt_debug_release(sk);
	sock_put(sk);

	return 0;
}