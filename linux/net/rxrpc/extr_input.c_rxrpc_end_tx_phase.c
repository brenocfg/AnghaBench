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
struct rxrpc_call {unsigned int state; int /*<<< orphan*/  tx_top; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  RXRPC_CALL_CLIENT_AWAIT_REPLY 130 
 unsigned int RXRPC_CALL_CLIENT_RECV_REPLY ; 
#define  RXRPC_CALL_CLIENT_SEND_REQUEST 129 
#define  RXRPC_CALL_SERVER_AWAIT_ACK 128 
 int /*<<< orphan*/  RXRPC_CALL_TX_LAST ; 
 int /*<<< orphan*/  __rxrpc_call_completed (struct rxrpc_call*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  kdebug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rxrpc_call_states ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_proto_abort (char const*,struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_transmit_await_reply ; 
 int /*<<< orphan*/  rxrpc_transmit_end ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_transmit (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rxrpc_end_tx_phase(struct rxrpc_call *call, bool reply_begun,
			       const char *abort_why)
{
	unsigned int state;

	ASSERT(test_bit(RXRPC_CALL_TX_LAST, &call->flags));

	write_lock(&call->state_lock);

	state = call->state;
	switch (state) {
	case RXRPC_CALL_CLIENT_SEND_REQUEST:
	case RXRPC_CALL_CLIENT_AWAIT_REPLY:
		if (reply_begun)
			call->state = state = RXRPC_CALL_CLIENT_RECV_REPLY;
		else
			call->state = state = RXRPC_CALL_CLIENT_AWAIT_REPLY;
		break;

	case RXRPC_CALL_SERVER_AWAIT_ACK:
		__rxrpc_call_completed(call);
		rxrpc_notify_socket(call);
		state = call->state;
		break;

	default:
		goto bad_state;
	}

	write_unlock(&call->state_lock);
	if (state == RXRPC_CALL_CLIENT_AWAIT_REPLY)
		trace_rxrpc_transmit(call, rxrpc_transmit_await_reply);
	else
		trace_rxrpc_transmit(call, rxrpc_transmit_end);
	_leave(" = ok");
	return true;

bad_state:
	write_unlock(&call->state_lock);
	kdebug("end_tx %s", rxrpc_call_states[call->state]);
	rxrpc_proto_abort(abort_why, call, call->tx_top);
	return false;
}