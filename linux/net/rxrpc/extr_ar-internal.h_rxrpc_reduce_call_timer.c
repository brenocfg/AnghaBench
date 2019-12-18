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
struct rxrpc_call {int /*<<< orphan*/  timer; } ;
typedef  enum rxrpc_timer_trace { ____Placeholder_rxrpc_timer_trace } rxrpc_timer_trace ;

/* Variables and functions */
 int /*<<< orphan*/  timer_reduce (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_rxrpc_timer (struct rxrpc_call*,int,unsigned long) ; 

__attribute__((used)) static inline void rxrpc_reduce_call_timer(struct rxrpc_call *call,
					   unsigned long expire_at,
					   unsigned long now,
					   enum rxrpc_timer_trace why)
{
	trace_rxrpc_timer(call, why, now);
	timer_reduce(&call->timer, expire_at);
}