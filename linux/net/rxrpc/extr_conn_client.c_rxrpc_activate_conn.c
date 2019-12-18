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
struct rxrpc_net {int /*<<< orphan*/  active_client_conns; int /*<<< orphan*/  nr_active_client_conns; } ;
struct rxrpc_connection {int /*<<< orphan*/  cache_link; int /*<<< orphan*/  cache_state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CONN_CLIENT_ACTIVE ; 
 int /*<<< orphan*/  RXRPC_CONN_CLIENT_UPGRADE ; 
 int /*<<< orphan*/  RXRPC_CONN_PROBING_FOR_UPGRADE ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_client_to_active ; 
 int /*<<< orphan*/  rxrpc_client_to_upgrade ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_client (struct rxrpc_connection*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_activate_conn(struct rxrpc_net *rxnet,
				struct rxrpc_connection *conn)
{
	if (test_bit(RXRPC_CONN_PROBING_FOR_UPGRADE, &conn->flags)) {
		trace_rxrpc_client(conn, -1, rxrpc_client_to_upgrade);
		conn->cache_state = RXRPC_CONN_CLIENT_UPGRADE;
	} else {
		trace_rxrpc_client(conn, -1, rxrpc_client_to_active);
		conn->cache_state = RXRPC_CONN_CLIENT_ACTIVE;
	}
	rxnet->nr_active_client_conns++;
	list_move_tail(&conn->cache_link, &rxnet->active_client_conns);
}