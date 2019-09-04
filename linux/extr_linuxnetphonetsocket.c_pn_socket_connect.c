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
struct task_struct {int dummy; } ;
struct socket {int state; struct sock* sk; } ;
struct sockaddr_pn {scalar_t__ spn_family; } ;
struct sockaddr {int dummy; } ;
struct sock {int sk_state; TYPE_1__* sk_prot; } ;
struct pn_sock {scalar_t__ dobject; int /*<<< orphan*/  resource; } ;
struct TYPE_2__ {int (* connect ) (struct sock*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 scalar_t__ AF_PHONET ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EAFNOSUPPORT ; 
 int EALREADY ; 
 int ECONNREFUSED ; 
 int ECONNRESET ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENOBUFS ; 
 int O_NONBLOCK ; 
 int const SS_CONNECTED ; 
#define  SS_CONNECTING 129 
#define  SS_UNCONNECTED 128 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int TCPF_ESTABLISHED ; 
 int TCPF_SYN_RECV ; 
 int TCP_CLOSE ; 
 int TCP_CLOSE_WAIT ; 
 int TCP_SYN_SENT ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 scalar_t__ pn_sockaddr_get_object (struct sockaddr_pn*) ; 
 int /*<<< orphan*/  pn_sockaddr_get_resource (struct sockaddr_pn*) ; 
 scalar_t__ pn_socket_autobind (struct socket*) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long schedule_timeout (long) ; 
 scalar_t__ signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int stub1 (struct sock*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int pn_socket_connect(struct socket *sock, struct sockaddr *addr,
		int len, int flags)
{
	struct sock *sk = sock->sk;
	struct pn_sock *pn = pn_sk(sk);
	struct sockaddr_pn *spn = (struct sockaddr_pn *)addr;
	struct task_struct *tsk = current;
	long timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);
	int err;

	if (pn_socket_autobind(sock))
		return -ENOBUFS;
	if (len < sizeof(struct sockaddr_pn))
		return -EINVAL;
	if (spn->spn_family != AF_PHONET)
		return -EAFNOSUPPORT;

	lock_sock(sk);

	switch (sock->state) {
	case SS_UNCONNECTED:
		if (sk->sk_state != TCP_CLOSE) {
			err = -EISCONN;
			goto out;
		}
		break;
	case SS_CONNECTING:
		err = -EALREADY;
		goto out;
	default:
		err = -EISCONN;
		goto out;
	}

	pn->dobject = pn_sockaddr_get_object(spn);
	pn->resource = pn_sockaddr_get_resource(spn);
	sock->state = SS_CONNECTING;

	err = sk->sk_prot->connect(sk, addr, len);
	if (err) {
		sock->state = SS_UNCONNECTED;
		pn->dobject = 0;
		goto out;
	}

	while (sk->sk_state == TCP_SYN_SENT) {
		DEFINE_WAIT(wait);

		if (!timeo) {
			err = -EINPROGRESS;
			goto out;
		}
		if (signal_pending(tsk)) {
			err = sock_intr_errno(timeo);
			goto out;
		}

		prepare_to_wait_exclusive(sk_sleep(sk), &wait,
						TASK_INTERRUPTIBLE);
		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock(sk);
		finish_wait(sk_sleep(sk), &wait);
	}

	if ((1 << sk->sk_state) & (TCPF_SYN_RECV|TCPF_ESTABLISHED))
		err = 0;
	else if (sk->sk_state == TCP_CLOSE_WAIT)
		err = -ECONNRESET;
	else
		err = -ECONNREFUSED;
	sock->state = err ? SS_UNCONNECTED : SS_CONNECTED;
out:
	release_sock(sk);
	return err;
}