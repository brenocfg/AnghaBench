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
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ sq_port; int /*<<< orphan*/  sq_node; int /*<<< orphan*/  sq_family; } ;
struct qrtr_sock {TYPE_1__ us; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_QIPCRTR ; 
 int ENOMEM ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  qrtr_local_nid ; 
 int /*<<< orphan*/  qrtr_proto ; 
 int /*<<< orphan*/  qrtr_proto_ops ; 
 struct qrtr_sock* qrtr_sk (struct sock*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qrtr_create(struct net *net, struct socket *sock,
		       int protocol, int kern)
{
	struct qrtr_sock *ipc;
	struct sock *sk;

	if (sock->type != SOCK_DGRAM)
		return -EPROTOTYPE;

	sk = sk_alloc(net, AF_QIPCRTR, GFP_KERNEL, &qrtr_proto, kern);
	if (!sk)
		return -ENOMEM;

	sock_set_flag(sk, SOCK_ZAPPED);

	sock_init_data(sock, sk);
	sock->ops = &qrtr_proto_ops;

	ipc = qrtr_sk(sk);
	ipc->us.sq_family = AF_QIPCRTR;
	ipc->us.sq_node = qrtr_local_nid;
	ipc->us.sq_port = 0;

	return 0;
}