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
struct rxrpc_net {unsigned int nr_client_conns; int /*<<< orphan*/  waiting_client_conns; int /*<<< orphan*/  client_conn_cache_lock; } ;
struct rxrpc_connection {int cache_state; int /*<<< orphan*/  cache_link; int /*<<< orphan*/  flags; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RXRPC_CONN_CLIENT_ACTIVE 133 
#define  RXRPC_CONN_CLIENT_CULLED 132 
#define  RXRPC_CONN_CLIENT_IDLE 131 
#define  RXRPC_CONN_CLIENT_INACTIVE 130 
#define  RXRPC_CONN_CLIENT_UPGRADE 129 
#define  RXRPC_CONN_CLIENT_WAITING 128 
 int /*<<< orphan*/  RXRPC_CONN_COUNTED ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_activate_conn (struct rxrpc_net*,struct rxrpc_connection*) ; 
 int /*<<< orphan*/  rxrpc_client_count ; 
 int /*<<< orphan*/  rxrpc_client_to_waiting ; 
 unsigned int rxrpc_max_client_connections ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_client (struct rxrpc_connection*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_animate_client_conn(struct rxrpc_net *rxnet,
				      struct rxrpc_connection *conn)
{
	unsigned int nr_conns;

	_enter("%d,%d", conn->debug_id, conn->cache_state);

	if (conn->cache_state == RXRPC_CONN_CLIENT_ACTIVE ||
	    conn->cache_state == RXRPC_CONN_CLIENT_UPGRADE)
		goto out;

	spin_lock(&rxnet->client_conn_cache_lock);

	nr_conns = rxnet->nr_client_conns;
	if (!test_and_set_bit(RXRPC_CONN_COUNTED, &conn->flags)) {
		trace_rxrpc_client(conn, -1, rxrpc_client_count);
		rxnet->nr_client_conns = nr_conns + 1;
	}

	switch (conn->cache_state) {
	case RXRPC_CONN_CLIENT_ACTIVE:
	case RXRPC_CONN_CLIENT_UPGRADE:
	case RXRPC_CONN_CLIENT_WAITING:
		break;

	case RXRPC_CONN_CLIENT_INACTIVE:
	case RXRPC_CONN_CLIENT_CULLED:
	case RXRPC_CONN_CLIENT_IDLE:
		if (nr_conns >= rxrpc_max_client_connections)
			goto wait_for_capacity;
		goto activate_conn;

	default:
		BUG();
	}

out_unlock:
	spin_unlock(&rxnet->client_conn_cache_lock);
out:
	_leave(" [%d]", conn->cache_state);
	return;

activate_conn:
	_debug("activate");
	rxrpc_activate_conn(rxnet, conn);
	goto out_unlock;

wait_for_capacity:
	_debug("wait");
	trace_rxrpc_client(conn, -1, rxrpc_client_to_waiting);
	conn->cache_state = RXRPC_CONN_CLIENT_WAITING;
	list_move_tail(&conn->cache_link, &rxnet->waiting_client_conns);
	goto out_unlock;
}