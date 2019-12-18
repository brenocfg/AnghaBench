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
struct xdp_sock {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  mutex; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct net {TYPE_1__ xdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_del_node_init_rcu (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int /*<<< orphan*/  xsk_delete_from_maps (struct xdp_sock*) ; 
 int /*<<< orphan*/  xsk_unbind_dev (struct xdp_sock*) ; 
 int /*<<< orphan*/  xskq_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsk_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);
	struct net *net;

	if (!sk)
		return 0;

	net = sock_net(sk);

	mutex_lock(&net->xdp.lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&net->xdp.lock);

	local_bh_disable();
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	local_bh_enable();

	xsk_delete_from_maps(xs);
	mutex_lock(&xs->mutex);
	xsk_unbind_dev(xs);
	mutex_unlock(&xs->mutex);

	xskq_destroy(xs->rx);
	xskq_destroy(xs->tx);

	sock_orphan(sk);
	sock->sk = NULL;

	sk_refcnt_debug_release(sk);
	sock_put(sk);

	return 0;
}