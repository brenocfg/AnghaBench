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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {int /*<<< orphan*/  expect_rx_by; int /*<<< orphan*/  next_rx_timo; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
#define  RXRPC_PACKET_TYPE_ABORT 132 
#define  RXRPC_PACKET_TYPE_ACK 131 
#define  RXRPC_PACKET_TYPE_ACKALL 130 
#define  RXRPC_PACKET_TYPE_BUSY 129 
#define  RXRPC_PACKET_TYPE_DATA 128 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _enter (char*,struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_input_abort (struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_input_ack (struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_input_ackall (struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_input_data (struct rxrpc_call*,struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_reduce_call_timer (struct rxrpc_call*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_skb_freed ; 
 int /*<<< orphan*/  rxrpc_timer_set_for_normal ; 

__attribute__((used)) static void rxrpc_input_call_packet(struct rxrpc_call *call,
				    struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	unsigned long timo;

	_enter("%p,%p", call, skb);

	timo = READ_ONCE(call->next_rx_timo);
	if (timo) {
		unsigned long now = jiffies, expect_rx_by;

		expect_rx_by = now + timo;
		WRITE_ONCE(call->expect_rx_by, expect_rx_by);
		rxrpc_reduce_call_timer(call, expect_rx_by, now,
					rxrpc_timer_set_for_normal);
	}

	switch (sp->hdr.type) {
	case RXRPC_PACKET_TYPE_DATA:
		rxrpc_input_data(call, skb);
		goto no_free;

	case RXRPC_PACKET_TYPE_ACK:
		rxrpc_input_ack(call, skb);
		break;

	case RXRPC_PACKET_TYPE_BUSY:
		_proto("Rx BUSY %%%u", sp->hdr.serial);

		/* Just ignore BUSY packets from the server; the retry and
		 * lifespan timers will take care of business.  BUSY packets
		 * from the client don't make sense.
		 */
		break;

	case RXRPC_PACKET_TYPE_ABORT:
		rxrpc_input_abort(call, skb);
		break;

	case RXRPC_PACKET_TYPE_ACKALL:
		rxrpc_input_ackall(call, skb);
		break;

	default:
		break;
	}

	rxrpc_free_skb(skb, rxrpc_skb_freed);
no_free:
	_leave("");
}