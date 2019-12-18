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
struct rxrpc_call {scalar_t__ acks_lost_ping; int /*<<< orphan*/  flags; int /*<<< orphan*/  ping_serial; int /*<<< orphan*/  ping_time; } ;
typedef  scalar_t__ rxrpc_serial_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXRPC_CALL_PINGING ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 scalar_t__ before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rxrpc_input_check_for_lost_ack (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_peer_add_rtt (struct rxrpc_call*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_rtt_rx_ping_response ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_input_ping_response(struct rxrpc_call *call,
				      ktime_t resp_time,
				      rxrpc_serial_t orig_serial,
				      rxrpc_serial_t ack_serial)
{
	rxrpc_serial_t ping_serial;
	ktime_t ping_time;

	ping_time = call->ping_time;
	smp_rmb();
	ping_serial = READ_ONCE(call->ping_serial);

	if (orig_serial == call->acks_lost_ping)
		rxrpc_input_check_for_lost_ack(call);

	if (before(orig_serial, ping_serial) ||
	    !test_and_clear_bit(RXRPC_CALL_PINGING, &call->flags))
		return;
	if (after(orig_serial, ping_serial))
		return;

	rxrpc_peer_add_rtt(call, rxrpc_rtt_rx_ping_response,
			   orig_serial, ack_serial, ping_time, resp_time);
}