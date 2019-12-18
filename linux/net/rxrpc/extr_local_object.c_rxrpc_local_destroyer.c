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
struct rxrpc_net {int /*<<< orphan*/  service_conn_reaper; int /*<<< orphan*/  local_mutex; } ;
struct rxrpc_local {int dead; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  reject_queue; struct socket* socket; int /*<<< orphan*/  service; int /*<<< orphan*/  link; int /*<<< orphan*/  debug_id; struct rxrpc_net* rxnet; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_clean_up_local_conns (struct rxrpc_local*) ; 
 int /*<<< orphan*/  rxrpc_purge_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_service_connection_reaper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static void rxrpc_local_destroyer(struct rxrpc_local *local)
{
	struct socket *socket = local->socket;
	struct rxrpc_net *rxnet = local->rxnet;

	_enter("%d", local->debug_id);

	local->dead = true;

	mutex_lock(&rxnet->local_mutex);
	list_del_init(&local->link);
	mutex_unlock(&rxnet->local_mutex);

	rxrpc_clean_up_local_conns(local);
	rxrpc_service_connection_reaper(&rxnet->service_conn_reaper);
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
}