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
struct socket {int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_PPPOX ; 
 int /*<<< orphan*/  PPPOX_NONE ; 
 int /*<<< orphan*/  PX_PROTO_OL2TP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  pppol2tp_backlog_recv ; 
 int /*<<< orphan*/  pppol2tp_ops ; 
 int /*<<< orphan*/  pppol2tp_session_destruct ; 
 int /*<<< orphan*/  pppol2tp_sk_proto ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int pppol2tp_create(struct net *net, struct socket *sock, int kern)
{
	int error = -ENOMEM;
	struct sock *sk;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pppol2tp_sk_proto, kern);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);

	sock->state  = SS_UNCONNECTED;
	sock->ops    = &pppol2tp_ops;

	sk->sk_backlog_rcv = pppol2tp_backlog_recv;
	sk->sk_protocol	   = PX_PROTO_OL2TP;
	sk->sk_family	   = PF_PPPOX;
	sk->sk_state	   = PPPOX_NONE;
	sk->sk_type	   = SOCK_STREAM;
	sk->sk_destruct	   = pppol2tp_session_destruct;

	error = 0;

out:
	return error;
}