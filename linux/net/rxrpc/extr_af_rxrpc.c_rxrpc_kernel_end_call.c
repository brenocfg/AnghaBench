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
struct socket {int /*<<< orphan*/  sk; } ;
struct rxrpc_call {int /*<<< orphan*/  user_mutex; int /*<<< orphan*/  notify_lock; scalar_t__ notify_rx; int /*<<< orphan*/  usage; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_call_put_kernel ; 
 scalar_t__ rxrpc_dummy_notify_rx ; 
 int /*<<< orphan*/  rxrpc_put_call (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_release_call (int /*<<< orphan*/ ,struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_kernel_end_call(struct socket *sock, struct rxrpc_call *call)
{
	_enter("%d{%d}", call->debug_id, atomic_read(&call->usage));

	mutex_lock(&call->user_mutex);
	rxrpc_release_call(rxrpc_sk(sock->sk), call);

	/* Make sure we're not going to call back into a kernel service */
	if (call->notify_rx) {
		spin_lock_bh(&call->notify_lock);
		call->notify_rx = rxrpc_dummy_notify_rx;
		spin_unlock_bh(&call->notify_lock);
	}

	mutex_unlock(&call->user_mutex);
	rxrpc_put_call(call, rxrpc_call_put_kernel);
}