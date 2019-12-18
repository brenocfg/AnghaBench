#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_rxrpc {int dummy; } ;
struct rxrpc_sock {int dummy; } ;
struct rxrpc_net {int /*<<< orphan*/  client_conn_reaper; } ;
struct rxrpc_conn_parameters {TYPE_1__* local; } ;
struct rxrpc_call {TYPE_4__* conn; int /*<<< orphan*/  error_link; int /*<<< orphan*/  user_call_ID; int /*<<< orphan*/  debug_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_9__ {TYPE_2__* peer; } ;
struct TYPE_10__ {TYPE_3__ params; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  error_targets; } ;
struct TYPE_7__ {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_activate_channels (TYPE_4__*) ; 
 int /*<<< orphan*/  rxrpc_animate_client_conn (struct rxrpc_net*,TYPE_4__*) ; 
 int /*<<< orphan*/  rxrpc_client_chan_wait_failed ; 
 int /*<<< orphan*/  rxrpc_cull_active_client_conns (struct rxrpc_net*) ; 
 int /*<<< orphan*/  rxrpc_discard_expired_client_conns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_disconnect_client_call (struct rxrpc_call*) ; 
 int rxrpc_get_client_conn (struct rxrpc_sock*,struct rxrpc_call*,struct rxrpc_conn_parameters*,struct sockaddr_rxrpc*,int /*<<< orphan*/ ) ; 
 int rxrpc_wait_for_channel (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_client (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

int rxrpc_connect_call(struct rxrpc_sock *rx,
		       struct rxrpc_call *call,
		       struct rxrpc_conn_parameters *cp,
		       struct sockaddr_rxrpc *srx,
		       gfp_t gfp)
{
	struct rxrpc_net *rxnet = cp->local->rxnet;
	int ret;

	_enter("{%d,%lx},", call->debug_id, call->user_call_ID);

	rxrpc_discard_expired_client_conns(&rxnet->client_conn_reaper);
	rxrpc_cull_active_client_conns(rxnet);

	ret = rxrpc_get_client_conn(rx, call, cp, srx, gfp);
	if (ret < 0)
		goto out;

	rxrpc_animate_client_conn(rxnet, call->conn);
	rxrpc_activate_channels(call->conn);

	ret = rxrpc_wait_for_channel(call, gfp);
	if (ret < 0) {
		trace_rxrpc_client(call->conn, ret, rxrpc_client_chan_wait_failed);
		rxrpc_disconnect_client_call(call);
		goto out;
	}

	spin_lock_bh(&call->conn->params.peer->lock);
	hlist_add_head_rcu(&call->error_link,
			   &call->conn->params.peer->error_targets);
	spin_unlock_bh(&call->conn->params.peer->lock);

out:
	_leave(" = %d", ret);
	return ret;
}