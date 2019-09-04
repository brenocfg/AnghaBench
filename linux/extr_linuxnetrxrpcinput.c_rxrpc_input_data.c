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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct rxrpc_wire_header {int dummy; } ;
struct TYPE_2__ {int seq; int flags; scalar_t__ serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_jumbo_header {int dummy; } ;
struct rxrpc_call {scalar_t__ rx_hard_ack; int rx_top; scalar_t__ state; scalar_t__ next_req_timo; int ackr_prev_seq; int rx_winsize; int nr_jumbo_bad; int* rxtx_annotations; int rx_expect_next; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  flags; struct sk_buff** rxtx_buffer; int /*<<< orphan*/  expect_req_by; } ;
typedef  scalar_t__ rxrpc_serial_t ;
typedef  int rxrpc_seq_t ;
typedef  enum rxrpc_call_state { ____Placeholder_rxrpc_call_state } rxrpc_call_state ;

/* Variables and functions */
 int READ_ONCE (scalar_t__) ; 
 int RXRPC_ACK_DELAY ; 
 int RXRPC_ACK_DUPLICATE ; 
 int RXRPC_ACK_EXCEEDS_WINDOW ; 
 int RXRPC_ACK_NOSPACE ; 
 int RXRPC_ACK_OUT_OF_SEQUENCE ; 
 int RXRPC_ACK_REQUESTED ; 
 int RXRPC_CALL_CLIENT_AWAIT_REPLY ; 
 int RXRPC_CALL_CLIENT_SEND_REQUEST ; 
 int RXRPC_CALL_COMPLETE ; 
 int /*<<< orphan*/  RXRPC_CALL_RX_LAST ; 
 scalar_t__ RXRPC_CALL_SERVER_RECV_REQUEST ; 
 scalar_t__ RXRPC_JUMBO_DATALEN ; 
 int RXRPC_JUMBO_PACKET ; 
 int RXRPC_LAST_PACKET ; 
 int RXRPC_REQUEST_ACK ; 
 int RXRPC_RXTX_BUFF_MASK ; 
 int RXRPC_RX_ANNO_JLAST ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _net (char*,int,int) ; 
 int /*<<< orphan*/  _proto (char*,scalar_t__,...) ; 
 scalar_t__ after (int,int) ; 
 scalar_t__ after_eq (int,int) ; 
 scalar_t__ before (int,int) ; 
 scalar_t__ before_eq (int,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_get_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_input_dup_data (struct rxrpc_call*,int,int,int*) ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_propose_ACK (struct rxrpc_call*,int,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_propose_ack_input_data ; 
 int /*<<< orphan*/  rxrpc_proto_abort (char*,struct rxrpc_call*,int) ; 
 int /*<<< orphan*/  rxrpc_receive_queue ; 
 int /*<<< orphan*/  rxrpc_receive_queue_last ; 
 int /*<<< orphan*/  rxrpc_receiving_reply (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_skb_rx_got ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_idle ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,unsigned int,int*,int) ; 
 int /*<<< orphan*/  smp_store_release (int*,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_notify_socket (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_rxrpc_receive (struct rxrpc_call*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_data (int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 

__attribute__((used)) static void rxrpc_input_data(struct rxrpc_call *call, struct sk_buff *skb,
			     u16 skew)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	enum rxrpc_call_state state;
	unsigned int offset = sizeof(struct rxrpc_wire_header);
	unsigned int ix;
	rxrpc_serial_t serial = sp->hdr.serial, ack_serial = 0;
	rxrpc_seq_t seq = sp->hdr.seq, hard_ack;
	bool immediate_ack = false, jumbo_bad = false, queued;
	u16 len;
	u8 ack = 0, flags, annotation = 0;

	_enter("{%u,%u},{%u,%u}",
	       call->rx_hard_ack, call->rx_top, skb->len, seq);

	_proto("Rx DATA %%%u { #%u f=%02x }",
	       sp->hdr.serial, seq, sp->hdr.flags);

	state = READ_ONCE(call->state);
	if (state >= RXRPC_CALL_COMPLETE)
		return;

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

	call->ackr_prev_seq = seq;

	hard_ack = READ_ONCE(call->rx_hard_ack);
	if (after(seq, hard_ack + call->rx_winsize)) {
		ack = RXRPC_ACK_EXCEEDS_WINDOW;
		ack_serial = serial;
		goto ack;
	}

	flags = sp->hdr.flags;
	if (flags & RXRPC_JUMBO_PACKET) {
		if (call->nr_jumbo_bad > 3) {
			ack = RXRPC_ACK_NOSPACE;
			ack_serial = serial;
			goto ack;
		}
		annotation = 1;
	}

next_subpacket:
	queued = false;
	ix = seq & RXRPC_RXTX_BUFF_MASK;
	len = skb->len;
	if (flags & RXRPC_JUMBO_PACKET)
		len = RXRPC_JUMBO_DATALEN;

	if (flags & RXRPC_LAST_PACKET) {
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

	trace_rxrpc_rx_data(call->debug_id, seq, serial, flags, annotation);
	if (before_eq(seq, hard_ack)) {
		ack = RXRPC_ACK_DUPLICATE;
		ack_serial = serial;
		goto skip;
	}

	if (flags & RXRPC_REQUEST_ACK && !ack) {
		ack = RXRPC_ACK_REQUESTED;
		ack_serial = serial;
	}

	if (call->rxtx_buffer[ix]) {
		rxrpc_input_dup_data(call, seq, annotation, &jumbo_bad);
		if (ack != RXRPC_ACK_DUPLICATE) {
			ack = RXRPC_ACK_DUPLICATE;
			ack_serial = serial;
		}
		immediate_ack = true;
		goto skip;
	}

	/* Queue the packet.  We use a couple of memory barriers here as need
	 * to make sure that rx_top is perceived to be set after the buffer
	 * pointer and that the buffer pointer is set after the annotation and
	 * the skb data.
	 *
	 * Barriers against rxrpc_recvmsg_data() and rxrpc_rotate_rx_window()
	 * and also rxrpc_fill_out_ack().
	 */
	rxrpc_get_skb(skb, rxrpc_skb_rx_got);
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
	if (flags & RXRPC_LAST_PACKET) {
		set_bit(RXRPC_CALL_RX_LAST, &call->flags);
		trace_rxrpc_receive(call, rxrpc_receive_queue_last, serial, seq);
	} else {
		trace_rxrpc_receive(call, rxrpc_receive_queue, serial, seq);
	}
	queued = true;

	if (after_eq(seq, call->rx_expect_next)) {
		if (after(seq, call->rx_expect_next)) {
			_net("OOS %u > %u", seq, call->rx_expect_next);
			ack = RXRPC_ACK_OUT_OF_SEQUENCE;
			ack_serial = serial;
		}
		call->rx_expect_next = seq + 1;
	}

skip:
	offset += len;
	if (flags & RXRPC_JUMBO_PACKET) {
		if (skb_copy_bits(skb, offset, &flags, 1) < 0) {
			rxrpc_proto_abort("XJF", call, seq);
			goto unlock;
		}
		offset += sizeof(struct rxrpc_jumbo_header);
		seq++;
		serial++;
		annotation++;
		if (flags & RXRPC_JUMBO_PACKET)
			annotation |= RXRPC_RX_ANNO_JLAST;
		if (after(seq, hard_ack + call->rx_winsize)) {
			ack = RXRPC_ACK_EXCEEDS_WINDOW;
			ack_serial = serial;
			if (!jumbo_bad) {
				call->nr_jumbo_bad++;
				jumbo_bad = true;
			}
			goto ack;
		}

		_proto("Rx DATA Jumbo %%%u", serial);
		goto next_subpacket;
	}

	if (queued && flags & RXRPC_LAST_PACKET && !ack) {
		ack = RXRPC_ACK_DELAY;
		ack_serial = serial;
	}

ack:
	if (ack)
		rxrpc_propose_ACK(call, ack, skew, ack_serial,
				  immediate_ack, true,
				  rxrpc_propose_ack_input_data);
	else
		rxrpc_propose_ACK(call, RXRPC_ACK_DELAY, skew, serial,
				  false, true,
				  rxrpc_propose_ack_input_data);

	if (sp->hdr.seq == READ_ONCE(call->rx_hard_ack) + 1) {
		trace_rxrpc_notify_socket(call->debug_id, serial);
		rxrpc_notify_socket(call);
	}

unlock:
	spin_unlock(&call->input_lock);
	_leave(" [queued]");
}