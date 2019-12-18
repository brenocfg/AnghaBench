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
struct rxrpc_wire_header {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_local {int /*<<< orphan*/  debug_id; int /*<<< orphan*/  event_queue; } ;

/* Variables and functions */
#define  RXRPC_PACKET_TYPE_VERSION 128 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  _proto (char*,char) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_see_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_send_version_request (struct rxrpc_local*,TYPE_1__*,struct sk_buff*) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxrpc_skb_freed ; 
 int /*<<< orphan*/  rxrpc_skb_seen ; 
 int /*<<< orphan*/  skb_copy_bits (struct sk_buff*,int,char*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void rxrpc_process_local_events(struct rxrpc_local *local)
{
	struct sk_buff *skb;
	char v;

	_enter("");

	skb = skb_dequeue(&local->event_queue);
	if (skb) {
		struct rxrpc_skb_priv *sp = rxrpc_skb(skb);

		rxrpc_see_skb(skb, rxrpc_skb_seen);
		_debug("{%d},{%u}", local->debug_id, sp->hdr.type);

		switch (sp->hdr.type) {
		case RXRPC_PACKET_TYPE_VERSION:
			if (skb_copy_bits(skb, sizeof(struct rxrpc_wire_header),
					  &v, 1) < 0)
				return;
			_proto("Rx VERSION { %02x }", v);
			if (v == 0)
				rxrpc_send_version_request(local, &sp->hdr, skb);
			break;

		default:
			/* Just ignore anything we don't understand */
			break;
		}

		rxrpc_free_skb(skb, rxrpc_skb_freed);
	}

	_leave("");
}