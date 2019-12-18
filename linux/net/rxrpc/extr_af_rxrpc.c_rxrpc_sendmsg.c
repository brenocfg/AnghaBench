#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct TYPE_7__ {int sk_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  family; } ;
struct TYPE_6__ {int transport_len; TYPE_1__ transport; int /*<<< orphan*/  transport_type; int /*<<< orphan*/  srx_service; int /*<<< orphan*/  srx_family; } ;
struct rxrpc_sock {TYPE_3__ sk; int /*<<< orphan*/  connect_srx; int /*<<< orphan*/  flags; struct rxrpc_local* local; TYPE_2__ srx; int /*<<< orphan*/  family; } ;
struct rxrpc_local {int dummy; } ;
struct msghdr {int msg_flags; int msg_namelen; int /*<<< orphan*/ * msg_name; } ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
 int /*<<< orphan*/  AF_RXRPC ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ERR (struct rxrpc_local*) ; 
 int MSG_OOB ; 
 int PTR_ERR (struct rxrpc_local*) ; 
#define  RXRPC_CLIENT_BOUND 132 
#define  RXRPC_CLIENT_UNBOUND 131 
#define  RXRPC_SERVER_BOUND 130 
#define  RXRPC_SERVER_LISTENING 129 
 int /*<<< orphan*/  RXRPC_SOCK_CONNECTED ; 
#define  RXRPC_UNBOUND 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  _enter (char*,int,size_t) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  lock_sock (TYPE_3__*) ; 
 int /*<<< orphan*/  release_sock (TYPE_3__*) ; 
 int rxrpc_do_sendmsg (struct rxrpc_sock*,struct msghdr*,size_t) ; 
 struct rxrpc_local* rxrpc_lookup_local (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 
 int rxrpc_validate_address (struct rxrpc_sock*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_sendmsg(struct socket *sock, struct msghdr *m, size_t len)
{
	struct rxrpc_local *local;
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);
	int ret;

	_enter(",{%d},,%zu", rx->sk.sk_state, len);

	if (m->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (m->msg_name) {
		ret = rxrpc_validate_address(rx, m->msg_name, m->msg_namelen);
		if (ret < 0) {
			_leave(" = %d [bad addr]", ret);
			return ret;
		}
	}

	lock_sock(&rx->sk);

	switch (rx->sk.sk_state) {
	case RXRPC_UNBOUND:
	case RXRPC_CLIENT_UNBOUND:
		rx->srx.srx_family = AF_RXRPC;
		rx->srx.srx_service = 0;
		rx->srx.transport_type = SOCK_DGRAM;
		rx->srx.transport.family = rx->family;
		switch (rx->family) {
		case AF_INET:
			rx->srx.transport_len = sizeof(struct sockaddr_in);
			break;
#ifdef CONFIG_AF_RXRPC_IPV6
		case AF_INET6:
			rx->srx.transport_len = sizeof(struct sockaddr_in6);
			break;
#endif
		default:
			ret = -EAFNOSUPPORT;
			goto error_unlock;
		}
		local = rxrpc_lookup_local(sock_net(sock->sk), &rx->srx);
		if (IS_ERR(local)) {
			ret = PTR_ERR(local);
			goto error_unlock;
		}

		rx->local = local;
		rx->sk.sk_state = RXRPC_CLIENT_BOUND;
		/* Fall through */

	case RXRPC_CLIENT_BOUND:
		if (!m->msg_name &&
		    test_bit(RXRPC_SOCK_CONNECTED, &rx->flags)) {
			m->msg_name = &rx->connect_srx;
			m->msg_namelen = sizeof(rx->connect_srx);
		}
		/* Fall through */
	case RXRPC_SERVER_BOUND:
	case RXRPC_SERVER_LISTENING:
		ret = rxrpc_do_sendmsg(rx, m, len);
		/* The socket has been unlocked */
		goto out;
	default:
		ret = -EINVAL;
		goto error_unlock;
	}

error_unlock:
	release_sock(&rx->sk);
out:
	_leave(" = %d", ret);
	return ret;
}