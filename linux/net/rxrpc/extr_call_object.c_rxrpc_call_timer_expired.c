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
struct timer_list {int dummy; } ;
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 struct rxrpc_call* call ; 
 struct rxrpc_call* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_timer_expired ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  trace_rxrpc_timer (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_call_timer_expired(struct timer_list *t)
{
	struct rxrpc_call *call = from_timer(call, t, timer);

	_enter("%d", call->debug_id);

	if (call->state < RXRPC_CALL_COMPLETE) {
		trace_rxrpc_timer(call, rxrpc_timer_expired, jiffies);
		rxrpc_queue_call(call);
	}
}