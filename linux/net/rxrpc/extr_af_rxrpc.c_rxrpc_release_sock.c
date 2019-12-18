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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct sock {int sk_state; TYPE_2__ sk_receive_queue; int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_refcnt; } ;
struct rxrpc_sock {int /*<<< orphan*/ * securities; int /*<<< orphan*/ * key; TYPE_1__* local; } ;
struct TYPE_3__ {int service_closed; int /*<<< orphan*/  services_lock; int /*<<< orphan*/  service; } ;

/* Variables and functions */
 int RXRPC_CLOSE ; 
#define  RXRPC_SERVER_BOUND 131 
#define  RXRPC_SERVER_BOUND2 130 
#define  RXRPC_SERVER_LISTENING 129 
#define  RXRPC_SERVER_LISTEN_DISABLED 128 
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int /*<<< orphan*/  _enter (char*,struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 struct rxrpc_sock* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_discard_prealloc (struct rxrpc_sock*) ; 
 int /*<<< orphan*/  rxrpc_purge_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  rxrpc_release_calls_on_socket (struct rxrpc_sock*) ; 
 struct rxrpc_sock* rxrpc_sk (struct sock*) ; 
 int /*<<< orphan*/  rxrpc_unuse_local (TYPE_1__*) ; 
 int /*<<< orphan*/  rxrpc_workqueue ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rxrpc_release_sock(struct sock *sk)
{
	struct rxrpc_sock *rx = rxrpc_sk(sk);

	_enter("%p{%d,%d}", sk, sk->sk_state, refcount_read(&sk->sk_refcnt));

	/* declare the socket closed for business */
	sock_orphan(sk);
	sk->sk_shutdown = SHUTDOWN_MASK;

	/* We want to kill off all connections from a service socket
	 * as fast as possible because we can't share these; client
	 * sockets, on the other hand, can share an endpoint.
	 */
	switch (sk->sk_state) {
	case RXRPC_SERVER_BOUND:
	case RXRPC_SERVER_BOUND2:
	case RXRPC_SERVER_LISTENING:
	case RXRPC_SERVER_LISTEN_DISABLED:
		rx->local->service_closed = true;
		break;
	}

	spin_lock_bh(&sk->sk_receive_queue.lock);
	sk->sk_state = RXRPC_CLOSE;
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	if (rx->local && rcu_access_pointer(rx->local->service) == rx) {
		write_lock(&rx->local->services_lock);
		rcu_assign_pointer(rx->local->service, NULL);
		write_unlock(&rx->local->services_lock);
	}

	/* try to flush out this socket */
	rxrpc_discard_prealloc(rx);
	rxrpc_release_calls_on_socket(rx);
	flush_workqueue(rxrpc_workqueue);
	rxrpc_purge_queue(&sk->sk_receive_queue);

	rxrpc_unuse_local(rx->local);
	rx->local = NULL;
	key_put(rx->key);
	rx->key = NULL;
	key_put(rx->securities);
	rx->securities = NULL;
	sock_put(sk);

	_leave(" = 0");
	return 0;
}