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
struct tipc_sock {long conn_timeout; int /*<<< orphan*/  peer; scalar_t__ group; } ;
struct socket {struct sock* sk; } ;
struct sockaddr_tipc {scalar_t__ family; scalar_t__ addrtype; } ;
struct sockaddr {int dummy; } ;
struct sock {int sk_state; } ;
struct msghdr {int msg_namelen; int /*<<< orphan*/  msg_flags; struct sockaddr* msg_name; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EALREADY ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int O_NONBLOCK ; 
#define  TIPC_CONNECTING 130 
#define  TIPC_ESTABLISHED 129 
#define  TIPC_OPEN 128 
 scalar_t__ TIPC_SERVICE_RANGE ; 
 int __tipc_sendmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 long msecs_to_jiffies (long) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 scalar_t__ tipc_sk_type_connectionless (struct sock*) ; 
 int /*<<< orphan*/  tipc_sockaddr_is_sane (struct sockaddr_tipc*) ; 
 int tipc_wait_for_connect (struct socket*,long*) ; 

__attribute__((used)) static int tipc_connect(struct socket *sock, struct sockaddr *dest,
			int destlen, int flags)
{
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk = tipc_sk(sk);
	struct sockaddr_tipc *dst = (struct sockaddr_tipc *)dest;
	struct msghdr m = {NULL,};
	long timeout = (flags & O_NONBLOCK) ? 0 : tsk->conn_timeout;
	int previous;
	int res = 0;

	if (destlen != sizeof(struct sockaddr_tipc))
		return -EINVAL;

	lock_sock(sk);

	if (tsk->group) {
		res = -EINVAL;
		goto exit;
	}

	if (dst->family == AF_UNSPEC) {
		memset(&tsk->peer, 0, sizeof(struct sockaddr_tipc));
		if (!tipc_sk_type_connectionless(sk))
			res = -EINVAL;
		goto exit;
	}
	if (!tipc_sockaddr_is_sane(dst)) {
		res = -EINVAL;
		goto exit;
	}
	/* DGRAM/RDM connect(), just save the destaddr */
	if (tipc_sk_type_connectionless(sk)) {
		memcpy(&tsk->peer, dest, destlen);
		goto exit;
	} else if (dst->addrtype == TIPC_SERVICE_RANGE) {
		res = -EINVAL;
		goto exit;
	}

	previous = sk->sk_state;

	switch (sk->sk_state) {
	case TIPC_OPEN:
		/* Send a 'SYN-' to destination */
		m.msg_name = dest;
		m.msg_namelen = destlen;

		/* If connect is in non-blocking case, set MSG_DONTWAIT to
		 * indicate send_msg() is never blocked.
		 */
		if (!timeout)
			m.msg_flags = MSG_DONTWAIT;

		res = __tipc_sendmsg(sock, &m, 0);
		if ((res < 0) && (res != -EWOULDBLOCK))
			goto exit;

		/* Just entered TIPC_CONNECTING state; the only
		 * difference is that return value in non-blocking
		 * case is EINPROGRESS, rather than EALREADY.
		 */
		res = -EINPROGRESS;
		/* fall through */
	case TIPC_CONNECTING:
		if (!timeout) {
			if (previous == TIPC_CONNECTING)
				res = -EALREADY;
			goto exit;
		}
		timeout = msecs_to_jiffies(timeout);
		/* Wait until an 'ACK' or 'RST' arrives, or a timeout occurs */
		res = tipc_wait_for_connect(sock, &timeout);
		break;
	case TIPC_ESTABLISHED:
		res = -EISCONN;
		break;
	default:
		res = -EINVAL;
	}

exit:
	release_sock(sk);
	return res;
}