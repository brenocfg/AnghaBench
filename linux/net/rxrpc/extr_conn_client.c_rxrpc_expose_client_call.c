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
struct rxrpc_connection {int /*<<< orphan*/  flags; struct rxrpc_channel* channels; } ;
struct rxrpc_channel {scalar_t__ call_counter; } ;
struct rxrpc_call {unsigned int cid; int /*<<< orphan*/  flags; struct rxrpc_connection* conn; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  RXRPC_CALL_EXPOSED ; 
 unsigned int RXRPC_CHANNELMASK ; 
 int /*<<< orphan*/  RXRPC_CONN_DONT_REUSE ; 
 int /*<<< orphan*/  rxrpc_expose_client_conn (struct rxrpc_connection*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rxrpc_expose_client_call(struct rxrpc_call *call)
{
	unsigned int channel = call->cid & RXRPC_CHANNELMASK;
	struct rxrpc_connection *conn = call->conn;
	struct rxrpc_channel *chan = &conn->channels[channel];

	if (!test_and_set_bit(RXRPC_CALL_EXPOSED, &call->flags)) {
		/* Mark the call ID as being used.  If the callNumber counter
		 * exceeds ~2 billion, we kill the connection after its
		 * outstanding calls have finished so that the counter doesn't
		 * wrap.
		 */
		chan->call_counter++;
		if (chan->call_counter >= INT_MAX)
			set_bit(RXRPC_CONN_DONT_REUSE, &conn->flags);
		rxrpc_expose_client_conn(conn, channel);
	}
}