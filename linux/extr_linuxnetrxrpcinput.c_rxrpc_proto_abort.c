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
struct rxrpc_call {int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  rxrpc_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  RXRPC_CALL_EV_ABORT ; 
 int /*<<< orphan*/  RX_PROTOCOL_ERROR ; 
 scalar_t__ rxrpc_abort_call (char const*,struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_proto_abort(const char *why,
			      struct rxrpc_call *call, rxrpc_seq_t seq)
{
	if (rxrpc_abort_call(why, call, seq, RX_PROTOCOL_ERROR, -EBADMSG)) {
		set_bit(RXRPC_CALL_EV_ABORT, &call->events);
		rxrpc_queue_call(call);
	}
}