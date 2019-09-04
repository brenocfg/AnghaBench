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
typedef  int /*<<< orphan*/  wtmp ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; } ;
struct rxrpc_wire_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  RXRPC_CALL_REMOTELY_ABORTED ; 
 int /*<<< orphan*/  RX_CALL_DEAD ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 scalar_t__ rxrpc_set_call_completion (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_abort (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_input_abort(struct rxrpc_call *call, struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	__be32 wtmp;
	u32 abort_code = RX_CALL_DEAD;

	_enter("");

	if (skb->len >= 4 &&
	    skb_copy_bits(skb, sizeof(struct rxrpc_wire_header),
			  &wtmp, sizeof(wtmp)) >= 0)
		abort_code = ntohl(wtmp);

	trace_rxrpc_rx_abort(call, sp->hdr.serial, abort_code);

	_proto("Rx ABORT %%%u { %x }", sp->hdr.serial, abort_code);

	if (rxrpc_set_call_completion(call, RXRPC_CALL_REMOTELY_ABORTED,
				      abort_code, -ECONNABORTED))
		rxrpc_notify_socket(call);
}