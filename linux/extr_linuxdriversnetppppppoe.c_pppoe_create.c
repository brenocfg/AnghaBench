#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  padt_work; } ;
struct TYPE_5__ {TYPE_1__ pppoe; } ;
struct TYPE_6__ {TYPE_2__ proto; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_PPPOX ; 
 int /*<<< orphan*/  PPPOX_NONE ; 
 int /*<<< orphan*/  PX_PROTO_OE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  pppoe_ops ; 
 int /*<<< orphan*/  pppoe_rcv_core ; 
 int /*<<< orphan*/  pppoe_sk_proto ; 
 int /*<<< orphan*/  pppoe_unbind_sock_work ; 
 TYPE_3__* pppox_sk (struct sock*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int pppoe_create(struct net *net, struct socket *sock, int kern)
{
	struct sock *sk;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pppoe_sk_proto, kern);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);

	sock->state	= SS_UNCONNECTED;
	sock->ops	= &pppoe_ops;

	sk->sk_backlog_rcv	= pppoe_rcv_core;
	sk->sk_state		= PPPOX_NONE;
	sk->sk_type		= SOCK_STREAM;
	sk->sk_family		= PF_PPPOX;
	sk->sk_protocol		= PX_PROTO_OE;

	INIT_WORK(&pppox_sk(sk)->proto.pppoe.padt_work,
		  pppoe_unbind_sock_work);

	return 0;
}