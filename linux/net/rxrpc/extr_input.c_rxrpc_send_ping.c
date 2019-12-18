#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  tstamp; } ;
struct TYPE_4__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_2__ hdr; } ;
struct rxrpc_call {TYPE_1__* peer; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int rtt_usage; int /*<<< orphan*/  rtt_last_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_ACK_PING ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_propose_ACK (struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_propose_ack_ping_for_params ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 

__attribute__((used)) static void rxrpc_send_ping(struct rxrpc_call *call, struct sk_buff *skb)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	ktime_t now = skb->tstamp;

	if (call->peer->rtt_usage < 3 ||
	    ktime_before(ktime_add_ms(call->peer->rtt_last_req, 1000), now))
		rxrpc_propose_ACK(call, RXRPC_ACK_PING, sp->hdr.serial,
				  true, true,
				  rxrpc_propose_ack_ping_for_params);
}