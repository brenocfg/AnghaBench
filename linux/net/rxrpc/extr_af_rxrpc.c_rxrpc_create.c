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
struct socket {scalar_t__ type; int /*<<< orphan*/  state; int /*<<< orphan*/ * ops; } ;
struct sock {int /*<<< orphan*/  sk_destruct; scalar_t__ sk_max_ack_backlog; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; } ;
struct rxrpc_sock {int family; int /*<<< orphan*/  sk; int /*<<< orphan*/  srx; int /*<<< orphan*/  call_lock; int /*<<< orphan*/  recvmsg_lock; int /*<<< orphan*/  recvmsg_q; int /*<<< orphan*/  to_be_accepted; int /*<<< orphan*/  sock_calls; int /*<<< orphan*/  incoming_lock; int /*<<< orphan*/  calls; } ;
struct rxrpc_net {int /*<<< orphan*/  peer_keepalive_timer; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_AF_RXRPC_IPV6 ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PF_INET ; 
 int PF_INET6 ; 
 int /*<<< orphan*/  PF_RXRPC ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RXRPC_UNBOUND ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RCU_FREE ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  _enter (char*,struct socket*,int) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_sock*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 struct rxrpc_net* rxrpc_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_proto ; 
 int /*<<< orphan*/  rxrpc_rpc_ops ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 
 int /*<<< orphan*/  rxrpc_sock_destructor ; 
 int /*<<< orphan*/  rxrpc_write_space ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_reduce (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int rxrpc_create(struct net *net, struct socket *sock, int protocol,
			int kern)
{
	struct rxrpc_net *rxnet;
	struct rxrpc_sock *rx;
	struct sock *sk;

	_enter("%p,%d", sock, protocol);

	/* we support transport protocol UDP/UDP6 only */
	if (protocol != PF_INET &&
	    IS_ENABLED(CONFIG_AF_RXRPC_IPV6) && protocol != PF_INET6)
		return -EPROTONOSUPPORT;

	if (sock->type != SOCK_DGRAM)
		return -ESOCKTNOSUPPORT;

	sock->ops = &rxrpc_rpc_ops;
	sock->state = SS_UNCONNECTED;

	sk = sk_alloc(net, PF_RXRPC, GFP_KERNEL, &rxrpc_proto, kern);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);
	sock_set_flag(sk, SOCK_RCU_FREE);
	sk->sk_state		= RXRPC_UNBOUND;
	sk->sk_write_space	= rxrpc_write_space;
	sk->sk_max_ack_backlog	= 0;
	sk->sk_destruct		= rxrpc_sock_destructor;

	rx = rxrpc_sk(sk);
	rx->family = protocol;
	rx->calls = RB_ROOT;

	spin_lock_init(&rx->incoming_lock);
	INIT_LIST_HEAD(&rx->sock_calls);
	INIT_LIST_HEAD(&rx->to_be_accepted);
	INIT_LIST_HEAD(&rx->recvmsg_q);
	rwlock_init(&rx->recvmsg_lock);
	rwlock_init(&rx->call_lock);
	memset(&rx->srx, 0, sizeof(rx->srx));

	rxnet = rxrpc_net(sock_net(&rx->sk));
	timer_reduce(&rxnet->peer_keepalive_timer, jiffies + 1);

	_leave(" = 0 [%p]", rx);
	return 0;
}