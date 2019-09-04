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
struct xdp_sock {int /*<<< orphan*/  tx_completion_lock; int /*<<< orphan*/  mutex; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_family; } ;
struct net {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int ENOBUFS ; 
 int EPERM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_XDP ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (struct net*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int /*<<< orphan*/  xsk_destruct ; 
 int /*<<< orphan*/  xsk_proto ; 
 int /*<<< orphan*/  xsk_proto_ops ; 

__attribute__((used)) static int xsk_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	struct sock *sk;
	struct xdp_sock *xs;

	if (!ns_capable(net->user_ns, CAP_NET_RAW))
		return -EPERM;
	if (sock->type != SOCK_RAW)
		return -ESOCKTNOSUPPORT;

	if (protocol)
		return -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	sk = sk_alloc(net, PF_XDP, GFP_KERNEL, &xsk_proto, kern);
	if (!sk)
		return -ENOBUFS;

	sock->ops = &xsk_proto_ops;

	sock_init_data(sock, sk);

	sk->sk_family = PF_XDP;

	sk->sk_destruct = xsk_destruct;
	sk_refcnt_debug_inc(sk);

	sock_set_flag(sk, SOCK_RCU_FREE);

	xs = xdp_sk(sk);
	mutex_init(&xs->mutex);
	spin_lock_init(&xs->tx_completion_lock);

	local_bh_disable();
	sock_prot_inuse_add(net, &xsk_proto, 1);
	local_bh_enable();

	return 0;
}