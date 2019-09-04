#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* peer; } ;
struct rxrpc_connection {int /*<<< orphan*/  idle_timestamp; int /*<<< orphan*/  channel_lock; TYPE_2__ params; } ;
struct rxrpc_call {struct rxrpc_connection* conn; int /*<<< orphan*/  error_link; int /*<<< orphan*/  cong_cwnd; TYPE_3__* peer; } ;
struct TYPE_6__ {int /*<<< orphan*/  cong_cwnd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rxrpc_disconnect_call (struct rxrpc_connection*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 void rxrpc_disconnect_client_call (struct rxrpc_call*) ; 
 scalar_t__ rxrpc_is_client_call (struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_put_connection (struct rxrpc_connection*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_disconnect_call(struct rxrpc_call *call)
{
	struct rxrpc_connection *conn = call->conn;

	call->peer->cong_cwnd = call->cong_cwnd;

	spin_lock_bh(&conn->params.peer->lock);
	hlist_del_rcu(&call->error_link);
	spin_unlock_bh(&conn->params.peer->lock);

	if (rxrpc_is_client_call(call))
		return rxrpc_disconnect_client_call(call);

	spin_lock(&conn->channel_lock);
	__rxrpc_disconnect_call(conn, call);
	spin_unlock(&conn->channel_lock);

	call->conn = NULL;
	conn->idle_timestamp = jiffies;
	rxrpc_put_connection(conn);
}