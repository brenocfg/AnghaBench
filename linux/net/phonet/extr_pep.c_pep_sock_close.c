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
struct sock {int sk_state; scalar_t__ sk_backlog_rcv; } ;
struct pep_sock {int ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAD ; 
 int /*<<< orphan*/  PNS_PEP_DISCONNECT_REQ ; 
 int TCPF_ESTABLISHED ; 
 int TCPF_SYN_RECV ; 
 int TCP_CLOSE ; 
 int /*<<< orphan*/  gprs_detach (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 scalar_t__ pipe_do_rcv ; 
 int /*<<< orphan*/  pipe_do_remove (struct sock*) ; 
 int /*<<< orphan*/  pipe_handler_request (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void pep_sock_close(struct sock *sk, long timeout)
{
	struct pep_sock *pn = pep_sk(sk);
	int ifindex = 0;

	sock_hold(sk); /* keep a reference after sk_common_release() */
	sk_common_release(sk);

	lock_sock(sk);
	if ((1 << sk->sk_state) & (TCPF_SYN_RECV|TCPF_ESTABLISHED)) {
		if (sk->sk_backlog_rcv == pipe_do_rcv)
			/* Forcefully remove dangling Phonet pipe */
			pipe_do_remove(sk);
		else
			pipe_handler_request(sk, PNS_PEP_DISCONNECT_REQ, PAD,
						NULL, 0);
	}
	sk->sk_state = TCP_CLOSE;

	ifindex = pn->ifindex;
	pn->ifindex = 0;
	release_sock(sk);

	if (ifindex)
		gprs_detach(sk);
	sock_put(sk);
}