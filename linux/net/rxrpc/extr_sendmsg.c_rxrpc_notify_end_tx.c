#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rxrpc_sock {int /*<<< orphan*/  sk; } ;
struct rxrpc_call {int /*<<< orphan*/  user_call_ID; } ;
typedef  int /*<<< orphan*/  (* rxrpc_notify_end_tx_t ) (int /*<<< orphan*/ *,struct rxrpc_call*,int /*<<< orphan*/ ) ;

/* Variables and functions */

__attribute__((used)) static void rxrpc_notify_end_tx(struct rxrpc_sock *rx, struct rxrpc_call *call,
				rxrpc_notify_end_tx_t notify_end_tx)
{
	if (notify_end_tx)
		notify_end_tx(&rx->sk, call, call->user_call_ID);
}