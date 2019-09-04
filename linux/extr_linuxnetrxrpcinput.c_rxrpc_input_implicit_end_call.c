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
struct rxrpc_sock {int /*<<< orphan*/  incoming_lock; } ;
struct rxrpc_connection {int dummy; } ;
struct rxrpc_call {int /*<<< orphan*/  events; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
#define  RXRPC_CALL_COMPLETE 129 
 int /*<<< orphan*/  RXRPC_CALL_EV_ABORT ; 
#define  RXRPC_CALL_SERVER_AWAIT_ACK 128 
 int /*<<< orphan*/  RX_CALL_DEAD ; 
 int /*<<< orphan*/  __rxrpc_disconnect_call (struct rxrpc_connection*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_abort_call (char*,struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_call_completed (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_improper_term (struct rxrpc_call*) ; 

__attribute__((used)) static void rxrpc_input_implicit_end_call(struct rxrpc_sock *rx,
					  struct rxrpc_connection *conn,
					  struct rxrpc_call *call)
{
	switch (READ_ONCE(call->state)) {
	case RXRPC_CALL_SERVER_AWAIT_ACK:
		rxrpc_call_completed(call);
		/* Fall through */
	case RXRPC_CALL_COMPLETE:
		break;
	default:
		if (rxrpc_abort_call("IMP", call, 0, RX_CALL_DEAD, -ESHUTDOWN)) {
			set_bit(RXRPC_CALL_EV_ABORT, &call->events);
			rxrpc_queue_call(call);
		}
		trace_rxrpc_improper_term(call);
		break;
	}

	spin_lock(&rx->incoming_lock);
	__rxrpc_disconnect_call(conn, call);
	spin_unlock(&rx->incoming_lock);
	rxrpc_notify_socket(call);
}