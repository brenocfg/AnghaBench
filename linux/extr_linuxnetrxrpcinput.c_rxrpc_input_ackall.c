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
struct TYPE_2__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {int /*<<< orphan*/  input_lock; int /*<<< orphan*/  tx_top; } ;
struct rxrpc_ack_summary {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  _proto (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_end_tx_phase (struct rxrpc_call*,int,char*) ; 
 scalar_t__ rxrpc_rotate_tx_window (struct rxrpc_call*,int /*<<< orphan*/ ,struct rxrpc_ack_summary*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_input_ackall(struct rxrpc_call *call, struct sk_buff *skb)
{
	struct rxrpc_ack_summary summary = { 0 };
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);

	_proto("Rx ACKALL %%%u", sp->hdr.serial);

	spin_lock(&call->input_lock);

	if (rxrpc_rotate_tx_window(call, call->tx_top, &summary))
		rxrpc_end_tx_phase(call, false, "ETL");

	spin_unlock(&call->input_lock);
}