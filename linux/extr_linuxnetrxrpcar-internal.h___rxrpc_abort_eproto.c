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
struct TYPE_2__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  serial; } ;
struct rxrpc_skb_priv {TYPE_1__ hdr; } ;
struct rxrpc_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTO ; 
 int rxrpc_abort_call (char const*,struct rxrpc_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_rxrpc_rx_eproto (struct rxrpc_call*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline bool __rxrpc_abort_eproto(struct rxrpc_call *call,
					struct sk_buff *skb,
					const char *eproto_why,
					const char *why,
					u32 abort_code)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);

	trace_rxrpc_rx_eproto(call, sp->hdr.serial, eproto_why);
	return rxrpc_abort_call(why, call, sp->hdr.seq, abort_code, -EPROTO);
}