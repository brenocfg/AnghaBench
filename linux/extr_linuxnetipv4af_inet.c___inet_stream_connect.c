#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {int state; struct sock* sk; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {int sk_state; scalar_t__ sk_protocol; TYPE_2__* sk_prot; } ;
struct TYPE_8__ {int /*<<< orphan*/  defer_connect; } ;
struct TYPE_7__ {TYPE_1__* fastopen_req; } ;
struct TYPE_6__ {int (* disconnect ) (struct sock*,int) ;int (* pre_connect ) (struct sock*,struct sockaddr*,int) ;int (* connect ) (struct sock*,struct sockaddr*,int) ;} ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  BPF_CGROUP_PRE_CONNECT_ENABLED (struct sock*) ; 
 int EALREADY ; 
 int ECONNABORTED ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 scalar_t__ IPPROTO_TCP ; 
 int O_NONBLOCK ; 
#define  SS_CONNECTED 130 
#define  SS_CONNECTING 129 
 int SS_DISCONNECTING ; 
#define  SS_UNCONNECTED 128 
 int TCPF_SYN_RECV ; 
 int TCPF_SYN_SENT ; 
 int TCP_CLOSE ; 
 int /*<<< orphan*/  current ; 
 TYPE_4__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_wait_for_connect (struct sock*,long,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int stub1 (struct sock*,int) ; 
 int stub2 (struct sock*,struct sockaddr*,int) ; 
 int stub3 (struct sock*,struct sockaddr*,int) ; 
 int stub4 (struct sock*,int) ; 
 TYPE_3__* tcp_sk (struct sock*) ; 

int __inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			  int addr_len, int flags, int is_sendmsg)
{
	struct sock *sk = sock->sk;
	int err;
	long timeo;

	/*
	 * uaddr can be NULL and addr_len can be 0 if:
	 * sk is a TCP fastopen active socket and
	 * TCP_FASTOPEN_CONNECT sockopt is set and
	 * we already have a valid cookie for this socket.
	 * In this case, user can call write() after connect().
	 * write() will invoke tcp_sendmsg_fastopen() which calls
	 * __inet_stream_connect().
	 */
	if (uaddr) {
		if (addr_len < sizeof(uaddr->sa_family))
			return -EINVAL;

		if (uaddr->sa_family == AF_UNSPEC) {
			err = sk->sk_prot->disconnect(sk, flags);
			sock->state = err ? SS_DISCONNECTING : SS_UNCONNECTED;
			goto out;
		}
	}

	switch (sock->state) {
	default:
		err = -EINVAL;
		goto out;
	case SS_CONNECTED:
		err = -EISCONN;
		goto out;
	case SS_CONNECTING:
		if (inet_sk(sk)->defer_connect)
			err = is_sendmsg ? -EINPROGRESS : -EISCONN;
		else
			err = -EALREADY;
		/* Fall out of switch with err, set for this state */
		break;
	case SS_UNCONNECTED:
		err = -EISCONN;
		if (sk->sk_state != TCP_CLOSE)
			goto out;

		if (BPF_CGROUP_PRE_CONNECT_ENABLED(sk)) {
			err = sk->sk_prot->pre_connect(sk, uaddr, addr_len);
			if (err)
				goto out;
		}

		err = sk->sk_prot->connect(sk, uaddr, addr_len);
		if (err < 0)
			goto out;

		sock->state = SS_CONNECTING;

		if (!err && inet_sk(sk)->defer_connect)
			goto out;

		/* Just entered SS_CONNECTING state; the only
		 * difference is that return value in non-blocking
		 * case is EINPROGRESS, rather than EALREADY.
		 */
		err = -EINPROGRESS;
		break;
	}

	timeo = sock_sndtimeo(sk, flags & O_NONBLOCK);

	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
		int writebias = (sk->sk_protocol == IPPROTO_TCP) &&
				tcp_sk(sk)->fastopen_req &&
				tcp_sk(sk)->fastopen_req->data ? 1 : 0;

		/* Error code is set above */
		if (!timeo || !inet_wait_for_connect(sk, timeo, writebias))
			goto out;

		err = sock_intr_errno(timeo);
		if (signal_pending(current))
			goto out;
	}

	/* Connection was closed by RST, timeout, ICMP error
	 * or another process disconnected us.
	 */
	if (sk->sk_state == TCP_CLOSE)
		goto sock_error;

	/* sk->sk_err may be not zero now, if RECVERR was ordered by user
	 * and error was received after socket entered established state.
	 * Hence, it is handled normally after connect() return successfully.
	 */

	sock->state = SS_CONNECTED;
	err = 0;
out:
	return err;

sock_error:
	err = sock_error(sk) ? : -ECONNABORTED;
	sock->state = SS_UNCONNECTED;
	if (sk->sk_prot->disconnect(sk, flags))
		sock->state = SS_DISCONNECTING;
	goto out;
}