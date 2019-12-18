#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wtmp ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rxrpc_wire_header {int dummy; } ;
struct TYPE_6__ {int type; int cid; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_3__ hdr; } ;
struct rxrpc_connection {scalar_t__ state; int error; int /*<<< orphan*/  channel_lock; int /*<<< orphan*/  state_lock; TYPE_2__* channels; TYPE_1__* security; int /*<<< orphan*/  abort_code; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  call; } ;
struct TYPE_4__ {int (* respond_to_challenge ) (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ;int (* verify_response ) (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ;int (* init_connection_security ) (struct rxrpc_connection*) ;int (* prime_packet_security ) (struct rxrpc_connection*) ;} ;

/* Variables and functions */
 int ECONNABORTED ; 
 int EPROTO ; 
 int /*<<< orphan*/  RXRPC_CALL_REMOTELY_ABORTED ; 
 int RXRPC_CHANNELMASK ; 
 scalar_t__ RXRPC_CONN_REMOTELY_ABORTED ; 
 scalar_t__ RXRPC_CONN_SERVICE ; 
 scalar_t__ RXRPC_CONN_SERVICE_CHALLENGING ; 
 int RXRPC_MAXCALLS ; 
#define  RXRPC_PACKET_TYPE_ABORT 133 
#define  RXRPC_PACKET_TYPE_ACK 132 
#define  RXRPC_PACKET_TYPE_BUSY 131 
#define  RXRPC_PACKET_TYPE_CHALLENGE 130 
#define  RXRPC_PACKET_TYPE_DATA 129 
#define  RXRPC_PACKET_TYPE_RESPONSE 128 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,scalar_t__) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_abort_calls (struct rxrpc_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_call_is_secure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_conn_retransmit_call (struct rxrpc_connection*,struct sk_buff*,int) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int stub2 (struct rxrpc_connection*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int stub3 (struct rxrpc_connection*) ; 
 int stub4 (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_eproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracepoint_string (char*) ; 

__attribute__((used)) static int rxrpc_process_event(struct rxrpc_connection *conn,
			       struct sk_buff *skb,
			       u32 *_abort_code)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	__be32 wtmp;
	u32 abort_code;
	int loop, ret;

	if (conn->state >= RXRPC_CONN_REMOTELY_ABORTED) {
		_leave(" = -ECONNABORTED [%u]", conn->state);
		return -ECONNABORTED;
	}

	_enter("{%d},{%u,%%%u},", conn->debug_id, sp->hdr.type, sp->hdr.serial);

	switch (sp->hdr.type) {
	case RXRPC_PACKET_TYPE_DATA:
	case RXRPC_PACKET_TYPE_ACK:
		rxrpc_conn_retransmit_call(conn, skb,
					   sp->hdr.cid & RXRPC_CHANNELMASK);
		return 0;

	case RXRPC_PACKET_TYPE_BUSY:
		/* Just ignore BUSY packets for now. */
		return 0;

	case RXRPC_PACKET_TYPE_ABORT:
		if (skb_copy_bits(skb, sizeof(struct rxrpc_wire_header),
				  &wtmp, sizeof(wtmp)) < 0) {
			trace_rxrpc_rx_eproto(NULL, sp->hdr.serial,
					      tracepoint_string("bad_abort"));
			return -EPROTO;
		}
		abort_code = ntohl(wtmp);
		_proto("Rx ABORT %%%u { ac=%d }", sp->hdr.serial, abort_code);

		conn->error = -ECONNABORTED;
		conn->abort_code = abort_code;
		conn->state = RXRPC_CONN_REMOTELY_ABORTED;
		rxrpc_abort_calls(conn, RXRPC_CALL_REMOTELY_ABORTED, sp->hdr.serial);
		return -ECONNABORTED;

	case RXRPC_PACKET_TYPE_CHALLENGE:
		return conn->security->respond_to_challenge(conn, skb,
							    _abort_code);

	case RXRPC_PACKET_TYPE_RESPONSE:
		ret = conn->security->verify_response(conn, skb, _abort_code);
		if (ret < 0)
			return ret;

		ret = conn->security->init_connection_security(conn);
		if (ret < 0)
			return ret;

		ret = conn->security->prime_packet_security(conn);
		if (ret < 0)
			return ret;

		spin_lock(&conn->channel_lock);
		spin_lock(&conn->state_lock);

		if (conn->state == RXRPC_CONN_SERVICE_CHALLENGING) {
			conn->state = RXRPC_CONN_SERVICE;
			spin_unlock(&conn->state_lock);
			for (loop = 0; loop < RXRPC_MAXCALLS; loop++)
				rxrpc_call_is_secure(
					rcu_dereference_protected(
						conn->channels[loop].call,
						lockdep_is_held(&conn->channel_lock)));
		} else {
			spin_unlock(&conn->state_lock);
		}

		spin_unlock(&conn->channel_lock);
		return 0;

	default:
		trace_rxrpc_rx_eproto(NULL, sp->hdr.serial,
				      tracepoint_string("bad_conn_pkt"));
		return -EPROTO;
	}
}