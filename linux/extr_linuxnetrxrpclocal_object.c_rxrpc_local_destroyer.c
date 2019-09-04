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
struct socket {TYPE_1__* sk; } ;
struct rxrpc_net {int /*<<< orphan*/  local_mutex; } ;
struct rxrpc_local {int dead; int /*<<< orphan*/  rcu; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  reject_queue; struct socket* socket; int /*<<< orphan*/  service; int /*<<< orphan*/  client_conns; int /*<<< orphan*/  link; struct rxrpc_net* rxnet; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_local_rcu ; 
 int /*<<< orphan*/  rxrpc_purge_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static void rxrpc_local_destroyer(struct rxrpc_local *local)
{
	struct socket *socket = local->socket;
	struct rxrpc_net *rxnet = local->rxnet;

	_enter("%d", local->debug_id);

	/* We can get a race between an incoming call packet queueing the
	 * processor again and the work processor starting the destruction
	 * process which will shut down the UDP socket.
	 */
	if (local->dead) {
		_leave(" [already dead]");
		return;
	}
	local->dead = true;

	mutex_lock(&rxnet->local_mutex);
	list_del_init(&local->link);
	mutex_unlock(&rxnet->local_mutex);

	ASSERT(RB_EMPTY_ROOT(&local->client_conns));
	ASSERT(!local->service);

	if (socket) {
		local->socket = NULL;
		kernel_sock_shutdown(socket, SHUT_RDWR);
		socket->sk->sk_user_data = NULL;
		sock_release(socket);
	}

	/* At this point, there should be no more packets coming in to the
	 * local endpoint.
	 */
	rxrpc_purge_queue(&local->reject_queue);
	rxrpc_purge_queue(&local->event_queue);

	_debug("rcu local %d", local->debug_id);
	call_rcu(&local->rcu, rxrpc_local_rcu);
}