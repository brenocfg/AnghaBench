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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_connection {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_eproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracepoint_string (char*) ; 

__attribute__((used)) static int none_respond_to_challenge(struct rxrpc_connection *conn,
				     struct sk_buff *skb,
				     u32 *_abort_code)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);

	trace_rxrpc_rx_eproto(NULL, sp->hdr.serial,
			      tracepoint_string("chall_none"));
	return -EPROTO;
}