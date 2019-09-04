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
struct socket {struct sock* sk; } ;
struct sockaddr_qrtr {int sq_port; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int sq_port; } ;
struct qrtr_sock {TYPE_1__ us; } ;

/* Variables and functions */
 int QRTR_PORT_CTRL ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int qrtr_port_assign (struct qrtr_sock*,int*) ; 
 int /*<<< orphan*/  qrtr_port_remove (struct qrtr_sock*) ; 
 int /*<<< orphan*/  qrtr_reset_ports () ; 
 struct qrtr_sock* qrtr_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __qrtr_bind(struct socket *sock,
		       const struct sockaddr_qrtr *addr, int zapped)
{
	struct qrtr_sock *ipc = qrtr_sk(sock->sk);
	struct sock *sk = sock->sk;
	int port;
	int rc;

	/* rebinding ok */
	if (!zapped && addr->sq_port == ipc->us.sq_port)
		return 0;

	port = addr->sq_port;
	rc = qrtr_port_assign(ipc, &port);
	if (rc)
		return rc;

	/* unbind previous, if any */
	if (!zapped)
		qrtr_port_remove(ipc);
	ipc->us.sq_port = port;

	sock_reset_flag(sk, SOCK_ZAPPED);

	/* Notify all open ports about the new controller */
	if (port == QRTR_PORT_CTRL)
		qrtr_reset_ports();

	return 0;
}