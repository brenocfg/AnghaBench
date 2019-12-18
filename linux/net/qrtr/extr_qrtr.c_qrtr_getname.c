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
struct sockaddr_qrtr {int /*<<< orphan*/  sq_family; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct qrtr_sock {struct sockaddr_qrtr us; struct sockaddr_qrtr peer; } ;
typedef  int /*<<< orphan*/  qaddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_QIPCRTR ; 
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_qrtr*,int) ; 
 struct qrtr_sock* qrtr_sk (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int qrtr_getname(struct socket *sock, struct sockaddr *saddr,
			int peer)
{
	struct qrtr_sock *ipc = qrtr_sk(sock->sk);
	struct sockaddr_qrtr qaddr;
	struct sock *sk = sock->sk;

	lock_sock(sk);
	if (peer) {
		if (sk->sk_state != TCP_ESTABLISHED) {
			release_sock(sk);
			return -ENOTCONN;
		}

		qaddr = ipc->peer;
	} else {
		qaddr = ipc->us;
	}
	release_sock(sk);

	qaddr.sq_family = AF_QIPCRTR;

	memcpy(saddr, &qaddr, sizeof(qaddr));

	return sizeof(qaddr);
}