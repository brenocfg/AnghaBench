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
struct rxrpc_call {int /*<<< orphan*/  ping_at; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_EV_PING ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long jiffies ; 
 unsigned long rxrpc_idle_ack_delay ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_ping ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_propose_ping(struct rxrpc_call *call,
			       bool immediate, bool background)
{
	if (immediate) {
		if (background &&
		    !test_and_set_bit(RXRPC_CALL_EV_PING, &call->events))
			rxrpc_queue_call(call);
	} else {
		unsigned long now = jiffies;
		unsigned long ping_at = now + rxrpc_idle_ack_delay;

		if (time_before(ping_at, call->ping_at)) {
			WRITE_ONCE(call->ping_at, ping_at);
			rxrpc_reduce_call_timer(call, ping_at, now,
						rxrpc_timer_set_for_ping);
		}
	}
}