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
struct rxrpc_call {int next_rx_timo; int /*<<< orphan*/  keepalive_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_keepalive ; 

__attribute__((used)) static void rxrpc_set_keepalive(struct rxrpc_call *call)
{
	unsigned long now = jiffies, keepalive_at = call->next_rx_timo / 6;

	keepalive_at += now;
	WRITE_ONCE(call->keepalive_at, keepalive_at);
	rxrpc_reduce_call_timer(call, keepalive_at, now,
				rxrpc_timer_set_for_keepalive);
}