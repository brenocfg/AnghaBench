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
struct rxrpc_call {int tx_phase; int /*<<< orphan*/  flags; int /*<<< orphan*/  ack_at; int /*<<< orphan*/  resend_at; int /*<<< orphan*/  lock; scalar_t__ ackr_reason; int /*<<< orphan*/  tx_top; } ;
struct rxrpc_ack_summary {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  rxrpc_seq_t ;

/* Variables and functions */
 unsigned long MAX_JIFFY_OFFSET ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXRPC_CALL_TX_LAST ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_end_tx_phase (struct rxrpc_call*,int,char*) ; 
 int /*<<< orphan*/  rxrpc_proto_abort (char*,struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_rotate_tx_window (struct rxrpc_call*,int /*<<< orphan*/ ,struct rxrpc_ack_summary*) ; 
 int /*<<< orphan*/  rxrpc_timer_init_for_reply ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_timer (struct rxrpc_call*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool rxrpc_receiving_reply(struct rxrpc_call *call)
{
	struct rxrpc_ack_summary summary = { 0 };
	unsigned long now, timo;
	rxrpc_seq_t top = READ_ONCE(call->tx_top);

	if (call->ackr_reason) {
		spin_lock_bh(&call->lock);
		call->ackr_reason = 0;
		spin_unlock_bh(&call->lock);
		now = jiffies;
		timo = now + MAX_JIFFY_OFFSET;
		WRITE_ONCE(call->resend_at, timo);
		WRITE_ONCE(call->ack_at, timo);
		trace_rxrpc_timer(call, rxrpc_timer_init_for_reply, now);
	}

	if (!test_bit(RXRPC_CALL_TX_LAST, &call->flags)) {
		if (!rxrpc_rotate_tx_window(call, top, &summary)) {
			rxrpc_proto_abort("TXL", call, top);
			return false;
		}
	}
	if (!rxrpc_end_tx_phase(call, true, "ETD"))
		return false;
	call->tx_phase = false;
	return true;
}