#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  x25_addr; } ;
struct x25_sock {int /*<<< orphan*/  state; int /*<<< orphan*/ * neighbour; int /*<<< orphan*/  dest_addr; TYPE_2__ source_addr; int /*<<< orphan*/  lci; int /*<<< orphan*/  facilities; } ;
struct x25_route {int /*<<< orphan*/  dev; } ;
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sockaddr_x25 {scalar_t__ sx25_family; int /*<<< orphan*/  sx25_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  x25_addr; } ;

/* Variables and functions */
 scalar_t__ AF_X25 ; 
 int ECONNREFUSED ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENETUNREACH ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 void* SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 void* SS_UNCONNECTED ; 
 scalar_t__ TCP_CLOSE ; 
 scalar_t__ TCP_ESTABLISHED ; 
 scalar_t__ TCP_SYN_SENT ; 
 int /*<<< orphan*/  X25_ADDR_LEN ; 
 int /*<<< orphan*/  X25_CALL_REQUEST ; 
 int /*<<< orphan*/  X25_STATE_0 ; 
 int /*<<< orphan*/  X25_STATE_1 ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int /*<<< orphan*/ ) ; 
 TYPE_1__ null_x25_address ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x25_get_neigh (int /*<<< orphan*/ ) ; 
 struct x25_route* x25_get_route (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_limit_facilities (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_list_lock ; 
 int /*<<< orphan*/  x25_neigh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_new_lci (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_route_put (struct x25_route*) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  x25_start_t21timer (struct sock*) ; 
 int x25_wait_for_connection_establishment (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25_connect(struct socket *sock, struct sockaddr *uaddr,
		       int addr_len, int flags)
{
	struct sock *sk = sock->sk;
	struct x25_sock *x25 = x25_sk(sk);
	struct sockaddr_x25 *addr = (struct sockaddr_x25 *)uaddr;
	struct x25_route *rt;
	int rc = 0;

	lock_sock(sk);
	if (sk->sk_state == TCP_ESTABLISHED && sock->state == SS_CONNECTING) {
		sock->state = SS_CONNECTED;
		goto out; /* Connect completed during a ERESTARTSYS event */
	}

	rc = -ECONNREFUSED;
	if (sk->sk_state == TCP_CLOSE && sock->state == SS_CONNECTING) {
		sock->state = SS_UNCONNECTED;
		goto out;
	}

	rc = -EISCONN;	/* No reconnect on a seqpacket socket */
	if (sk->sk_state == TCP_ESTABLISHED)
		goto out;

	sk->sk_state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	rc = -EINVAL;
	if (addr_len != sizeof(struct sockaddr_x25) ||
	    addr->sx25_family != AF_X25)
		goto out;

	rc = -ENETUNREACH;
	rt = x25_get_route(&addr->sx25_addr);
	if (!rt)
		goto out;

	x25->neighbour = x25_get_neigh(rt->dev);
	if (!x25->neighbour)
		goto out_put_route;

	x25_limit_facilities(&x25->facilities, x25->neighbour);

	x25->lci = x25_new_lci(x25->neighbour);
	if (!x25->lci)
		goto out_put_neigh;

	rc = -EINVAL;
	if (sock_flag(sk, SOCK_ZAPPED)) /* Must bind first - autobinding does not work */
		goto out_put_neigh;

	if (!strcmp(x25->source_addr.x25_addr, null_x25_address.x25_addr))
		memset(&x25->source_addr, '\0', X25_ADDR_LEN);

	x25->dest_addr = addr->sx25_addr;

	/* Move to connecting socket, start sending Connect Requests */
	sock->state   = SS_CONNECTING;
	sk->sk_state  = TCP_SYN_SENT;

	x25->state = X25_STATE_1;

	x25_write_internal(sk, X25_CALL_REQUEST);

	x25_start_heartbeat(sk);
	x25_start_t21timer(sk);

	/* Now the loop */
	rc = -EINPROGRESS;
	if (sk->sk_state != TCP_ESTABLISHED && (flags & O_NONBLOCK))
		goto out_put_neigh;

	rc = x25_wait_for_connection_establishment(sk);
	if (rc)
		goto out_put_neigh;

	sock->state = SS_CONNECTED;
	rc = 0;
out_put_neigh:
	if (rc) {
		read_lock_bh(&x25_list_lock);
		x25_neigh_put(x25->neighbour);
		x25->neighbour = NULL;
		read_unlock_bh(&x25_list_lock);
		x25->state = X25_STATE_0;
	}
out_put_route:
	x25_route_put(rt);
out:
	release_sock(sk);
	return rc;
}