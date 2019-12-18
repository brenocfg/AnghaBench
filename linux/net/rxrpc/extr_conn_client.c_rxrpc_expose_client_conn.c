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
struct rxrpc_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CONN_EXPOSED ; 
 int /*<<< orphan*/  rxrpc_client_exposed ; 
 int /*<<< orphan*/  rxrpc_get_connection (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_client (struct rxrpc_connection*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_expose_client_conn(struct rxrpc_connection *conn,
				     unsigned int channel)
{
	if (!test_and_set_bit(RXRPC_CONN_EXPOSED, &conn->flags)) {
		trace_rxrpc_client(conn, channel, rxrpc_client_exposed);
		rxrpc_get_connection(conn);
	}
}