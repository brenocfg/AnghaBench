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
struct rxrpc_connection {int /*<<< orphan*/  debug_id; struct rxrpc_channel* channels; } ;
struct rxrpc_channel {int /*<<< orphan*/  call; int /*<<< orphan*/  call_counter; int /*<<< orphan*/  call_id; int /*<<< orphan*/  last_call; void* last_type; int /*<<< orphan*/  last_abort; int /*<<< orphan*/  last_seq; } ;
struct rxrpc_call {size_t cid; int completion; int /*<<< orphan*/  abort_code; int /*<<< orphan*/  rx_hard_ack; } ;

/* Variables and functions */
#define  RXRPC_CALL_LOCALLY_ABORTED 129 
#define  RXRPC_CALL_SUCCEEDED 128 
 size_t RXRPC_CHANNELMASK ; 
 void* RXRPC_PACKET_TYPE_ABORT ; 
 void* RXRPC_PACKET_TYPE_ACK ; 
 int /*<<< orphan*/  RX_USER_ABORT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 struct rxrpc_call* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  trace_rxrpc_disconnect_call (struct rxrpc_call*) ; 

void __rxrpc_disconnect_call(struct rxrpc_connection *conn,
			     struct rxrpc_call *call)
{
	struct rxrpc_channel *chan =
		&conn->channels[call->cid & RXRPC_CHANNELMASK];

	_enter("%d,%x", conn->debug_id, call->cid);

	if (rcu_access_pointer(chan->call) == call) {
		/* Save the result of the call so that we can repeat it if necessary
		 * through the channel, whilst disposing of the actual call record.
		 */
		trace_rxrpc_disconnect_call(call);
		switch (call->completion) {
		case RXRPC_CALL_SUCCEEDED:
			chan->last_seq = call->rx_hard_ack;
			chan->last_type = RXRPC_PACKET_TYPE_ACK;
			break;
		case RXRPC_CALL_LOCALLY_ABORTED:
			chan->last_abort = call->abort_code;
			chan->last_type = RXRPC_PACKET_TYPE_ABORT;
			break;
		default:
			chan->last_abort = RX_USER_ABORT;
			chan->last_type = RXRPC_PACKET_TYPE_ABORT;
			break;
		}

		/* Sync with rxrpc_conn_retransmit(). */
		smp_wmb();
		chan->last_call = chan->call_id;
		chan->call_id = chan->call_counter;

		rcu_assign_pointer(chan->call, NULL);
	}

	_leave("");
}