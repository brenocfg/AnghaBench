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
struct rxrpc_sock {int dummy; } ;
struct rxrpc_call {int /*<<< orphan*/  waitq; int /*<<< orphan*/  tx_winsize; int /*<<< orphan*/  tx_top; int /*<<< orphan*/  tx_hard_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rxrpc_wait_for_tx_window_intr (struct rxrpc_sock*,struct rxrpc_call*,long*) ; 
 int rxrpc_wait_for_tx_window_nonintr (struct rxrpc_sock*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxrpc_wait_for_tx_window(struct rxrpc_sock *rx,
				    struct rxrpc_call *call,
				    long *timeo,
				    bool waitall)
{
	DECLARE_WAITQUEUE(myself, current);
	int ret;

	_enter(",{%u,%u,%u}",
	       call->tx_hard_ack, call->tx_top, call->tx_winsize);

	add_wait_queue(&call->waitq, &myself);

	if (waitall)
		ret = rxrpc_wait_for_tx_window_nonintr(rx, call);
	else
		ret = rxrpc_wait_for_tx_window_intr(rx, call, timeo);

	remove_wait_queue(&call->waitq, &myself);
	set_current_state(TASK_RUNNING);
	_leave(" = %d", ret);
	return ret;
}