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
struct rxrpc_call {scalar_t__ state; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 scalar_t__ RXRPC_CALL_SERVER_ACCEPTING ; 
 scalar_t__ RXRPC_CALL_SERVER_SECURING ; 
 int /*<<< orphan*/  _enter (char*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_notify_socket (struct rxrpc_call*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_call_is_secure(struct rxrpc_call *call)
{
	_enter("%p", call);
	if (call) {
		write_lock_bh(&call->state_lock);
		if (call->state == RXRPC_CALL_SERVER_SECURING) {
			call->state = RXRPC_CALL_SERVER_ACCEPTING;
			rxrpc_notify_socket(call);
		}
		write_unlock_bh(&call->state_lock);
	}
}