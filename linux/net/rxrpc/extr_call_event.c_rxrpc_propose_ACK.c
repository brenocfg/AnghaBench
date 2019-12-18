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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rxrpc_call {int /*<<< orphan*/  lock; } ;
typedef  enum rxrpc_propose_ack_trace { ____Placeholder_rxrpc_propose_ack_trace } rxrpc_propose_ack_trace ;

/* Variables and functions */
 int /*<<< orphan*/  __rxrpc_propose_ACK (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_propose_ACK(struct rxrpc_call *call, u8 ack_reason,
		       u32 serial, bool immediate, bool background,
		       enum rxrpc_propose_ack_trace why)
{
	spin_lock_bh(&call->lock);
	__rxrpc_propose_ACK(call, ack_reason, serial,
			    immediate, background, why);
	spin_unlock_bh(&call->lock);
}