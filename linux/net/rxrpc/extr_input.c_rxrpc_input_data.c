#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {unsigned int seq; scalar_t__ serial; int /*<<< orphan*/  flags; } ;
struct rxrpc_skb_priv {int nr_subpackets; int rx_flags; int /*<<< orphan*/ * rx_req_ack; TYPE_1__ hdr; } ;
struct rxrpc_call {scalar_t__ rx_hard_ack; unsigned int rx_top; scalar_t__ state; scalar_t__ next_req_timo; unsigned int ackr_prev_seq; int nr_jumbo_bad; unsigned int rx_winsize; unsigned int rx_expect_next; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  flags; struct sk_buff** rxtx_buffer; scalar_t__* rxtx_annotations; int /*<<< orphan*/  expect_req_by; } ;
typedef  scalar_t__ rxrpc_serial_t ;
typedef  unsigned int rxrpc_seq_t ;
typedef  enum rxrpc_call_state { ____Placeholder_rxrpc_call_state } rxrpc_call_state ;

/* Variables and functions */
 int READ_ONCE (scalar_t__) ; 
 scalar_t__ RXRPC_ACK_DELAY ; 
 scalar_t__ RXRPC_ACK_DUPLICATE ; 
 scalar_t__ RXRPC_ACK_EXCEEDS_WINDOW ; 
 scalar_t__ RXRPC_ACK_NOSPACE ; 
 scalar_t__ RXRPC_ACK_OUT_OF_SEQUENCE ; 
 scalar_t__ RXRPC_ACK_REQUESTED ; 
 int RXRPC_CALL_CLIENT_AWAIT_REPLY ; 
 int RXRPC_CALL_CLIENT_SEND_REQUEST ; 
 int RXRPC_CALL_COMPLETE ; 
 unsigned int RXRPC_CALL_RX_LAST ; 
 scalar_t__ RXRPC_CALL_SERVER_RECV_REQUEST ; 
 scalar_t__ RXRPC_JUMBO_PACKET ; 
 scalar_t__ RXRPC_LAST_PACKET ; 
 scalar_t__ RXRPC_REQUEST_ACK ; 
 unsigned int RXRPC_RXTX_BUFF_MASK ; 
 int RXRPC_SKB_INCL_LAST ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _net (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _proto (char*,unsigned int,unsigned int,unsigned int,int,...) ; 
 scalar_t__ after (unsigned int,unsigned int) ; 
 scalar_t__ after_eq (unsigned int,unsigned int) ; 
 scalar_t__ before (unsigned int,unsigned int) ; 
 scalar_t__ before_eq (unsigned int,unsigned int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_get_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_input_dup_data (struct rxrpc_call*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_propose_ACK (struct rxrpc_call*,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_propose_ack_input_data ; 
 int /*<<< orphan*/  rxrpc_proto_abort (char*,struct rxrpc_call*,unsigned int) ; 
 int /*<<< orphan*/  rxrpc_receive_queue ; 
 int /*<<< orphan*/  rxrpc_receive_queue_last ; 
 int /*<<< orphan*/  rxrpc_receiving_reply (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_skb_freed ; 
 int /*<<< orphan*/  rxrpc_skb_got ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_idle ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_notify_socket (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_rxrpc_receive (struct rxrpc_call*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_data (int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rxrpc_input_data(struct rxrpc_call *call, struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	enum rxrpc_call_state state;
	unsigned int j;
	rxrpc_serial_t serial = sp->hdr.serial, ack_serial = 0;
	rxrpc_seq_t seq0 = sp->hdr.seq, hard_ack;
	bool immediate_ack = false, jumbo_bad = false;
	u8 ack = 0;

	_enter("{%u,%u},{%u,%u}",
	       call->rx_hard_ack, call->rx_top, skb->len, seq0);

	_proto("Rx DATA %%%u { #%u f=%02x n=%u }",
	       sp->hdr.serial, seq0, sp->hdr.flags, sp->nr_subpackets);

	state = READ_ONCE(call->state);
	if (state >= RXRPC_CALL_COMPLETE) {
		rxrpc_free_skb(skb, rxrpc_skb_freed);
		return;
	}

	if (call->state == RXRPC_CALL_SERVER_RECV_REQUEST) {
		unsigned long timo = READ_ONCE(call->next_req_timo);
		unsigned long now, expect_req_by;

		if (timo) {
			now = jiffies;
			expect_req_by = now + timo;
			WRITE_ONCE(call->expect_req_by, expect_req_by);
			rxrpc_reduce_call_timer(call, expect_req_by, now,
						rxrpc_timer_set_for_idle);
		}
	}

	spin_lock(&call->input_lock);

	/* Received data implicitly ACKs all of the request packets we sent
	 * when we're acting as a client.
	 */
	if ((state == RXRPC_CALL_CLIENT_SEND_REQUEST ||
	     state == RXRPC_CALL_CLIENT_AWAIT_REPLY) &&
	    !rxrpc_receiving_reply(call))
		goto unlock;

	call->ackr_prev_seq = seq0;
	hard_ack = READ_ONCE(call->rx_hard_ack);

	if (sp->nr_subpackets > 1) {
		if (call->nr_jumbo_bad > 3) {
			ack = RXRPC_ACK_NOSPACE;
			ack_serial = serial;
			goto ack;
		}
	}

	for (j = 0; j < sp->nr_subpackets; j++) {
		rxrpc_serial_t serial = sp->hdr.serial + j;
		rxrpc_seq_t seq = seq0 + j;
		unsigned int ix = seq & RXRPC_RXTX_BUFF_MASK;
		bool terminal = (j == sp->nr_subpackets - 1);
		bool last = terminal && (sp->rx_flags & RXRPC_SKB_INCL_LAST);
		u8 flags, annotation = j;

		_proto("Rx DATA+%u %%%u { #%x t=%u l=%u }",
		     j, serial, seq, terminal, last);

		if (last) {
			if (test_bit(RXRPC_CALL_RX_LAST, &call->flags) &&
			    seq != call->rx_top) {
				rxrpc_proto_abort("LSN", call, seq);
				goto unlock;
			}
		} else {
			if (test_bit(RXRPC_CALL_RX_LAST, &call->flags) &&
			    after_eq(seq, call->rx_top)) {
				rxrpc_proto_abort("LSA", call, seq);
				goto unlock;
			}
		}

		flags = 0;
		if (last)
			flags |= RXRPC_LAST_PACKET;
		if (!terminal)
			flags |= RXRPC_JUMBO_PACKET;
		if (test_bit(j, sp->rx_req_ack))
			flags |= RXRPC_REQUEST_ACK;
		trace_rxrpc_rx_data(call->debug_id, seq, serial, flags, annotation);

		if (before_eq(seq, hard_ack)) {
			ack = RXRPC_ACK_DUPLICATE;
			ack_serial = serial;
			continue;
		}

		if (call->rxtx_buffer[ix]) {
			rxrpc_input_dup_data(call, seq, sp->nr_subpackets > 1,
					     &jumbo_bad);
			if (ack != RXRPC_ACK_DUPLICATE) {
				ack = RXRPC_ACK_DUPLICATE;
				ack_serial = serial;
			}
			immediate_ack = true;
			continue;
		}

		if (after(seq, hard_ack + call->rx_winsize)) {
			ack = RXRPC_ACK_EXCEEDS_WINDOW;
			ack_serial = serial;
			if (flags & RXRPC_JUMBO_PACKET) {
				if (!jumbo_bad) {
					call->nr_jumbo_bad++;
					jumbo_bad = true;
				}
			}

			goto ack;
		}

		if (flags & RXRPC_REQUEST_ACK && !ack) {
			ack = RXRPC_ACK_REQUESTED;
			ack_serial = serial;
		}

		/* Queue the packet.  We use a couple of memory barriers here as need
		 * to make sure that rx_top is perceived to be set after the buffer
		 * pointer and that the buffer pointer is set after the annotation and
		 * the skb data.
		 *
		 * Barriers against rxrpc_recvmsg_data() and rxrpc_rotate_rx_window()
		 * and also rxrpc_fill_out_ack().
		 */
		if (!terminal)
			rxrpc_get_skb(skb, rxrpc_skb_got);
		call->rxtx_annotations[ix] = annotation;
		smp_wmb();
		call->rxtx_buffer[ix] = skb;
		if (after(seq, call->rx_top)) {
			smp_store_release(&call->rx_top, seq);
		} else if (before(seq, call->rx_top)) {
			/* Send an immediate ACK if we fill in a hole */
			if (!ack) {
				ack = RXRPC_ACK_DELAY;
				ack_serial = serial;
			}
			immediate_ack = true;
		}

		if (terminal) {
			/* From this point on, we're not allowed to touch the
			 * packet any longer as its ref now belongs to the Rx
			 * ring.
			 */
			skb = NULL;
		}

		if (last) {
			set_bit(RXRPC_CALL_RX_LAST, &call->flags);
			if (!ack) {
				ack = RXRPC_ACK_DELAY;
				ack_serial = serial;
			}
			trace_rxrpc_receive(call, rxrpc_receive_queue_last, serial, seq);
		} else {
			trace_rxrpc_receive(call, rxrpc_receive_queue, serial, seq);
		}

		if (after_eq(seq, call->rx_expect_next)) {
			if (after(seq, call->rx_expect_next)) {
				_net("OOS %u > %u", seq, call->rx_expect_next);
				ack = RXRPC_ACK_OUT_OF_SEQUENCE;
				ack_serial = serial;
			}
			call->rx_expect_next = seq + 1;
		}
	}

ack:
	if (ack)
		rxrpc_propose_ACK(call, ack, ack_serial,
				  immediate_ack, true,
				  rxrpc_propose_ack_input_data);
	else
		rxrpc_propose_ACK(call, RXRPC_ACK_DELAY, serial,
				  false, true,
				  rxrpc_propose_ack_input_data);

	if (seq0 == READ_ONCE(call->rx_hard_ack) + 1) {
		trace_rxrpc_notify_socket(call->debug_id, serial);
		rxrpc_notify_socket(call);
	}

unlock:
	spin_unlock(&call->input_lock);
	rxrpc_free_skb(skb, rxrpc_skb_freed);
	_leave(" [queued]");
}