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
struct rxrpc_call {scalar_t__ state; int* rxtx_annotations; int /*<<< orphan*/  lock; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  RXRPC_CALL_EV_RESEND ; 
 int RXRPC_TX_ANNO_LAST ; 
 int RXRPC_TX_ANNO_RETRANS ; 
 int /*<<< orphan*/  rxrpc_queue_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rxrpc_instant_resend(struct rxrpc_call *call, int ix)
{
	spin_lock_bh(&call->lock);

	if (call->state < RXRPC_CALL_COMPLETE) {
		call->rxtx_annotations[ix] =
			(call->rxtx_annotations[ix] & RXRPC_TX_ANNO_LAST) |
			RXRPC_TX_ANNO_RETRANS;
		if (!test_and_set_bit(RXRPC_CALL_EV_RESEND, &call->events))
			rxrpc_queue_call(call);
	}

	spin_unlock_bh(&call->lock);
}