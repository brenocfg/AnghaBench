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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr_rxrpc {int /*<<< orphan*/  srx_service; } ;
struct rxrpc_sock {int /*<<< orphan*/  local; struct key* key; } ;
struct rxrpc_conn_parameters {int exclusive; int /*<<< orphan*/  peer; int /*<<< orphan*/  service_id; scalar_t__ security_level; struct key* key; int /*<<< orphan*/  local; } ;
struct rxrpc_call {int /*<<< orphan*/  user_mutex; int /*<<< orphan*/  usage; int /*<<< orphan*/  debug_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rxrpc_conn_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rxrpc_prepare_call_for_retry (struct rxrpc_sock*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  rxrpc_put_peer (int /*<<< orphan*/ ) ; 
 int rxrpc_retry_client_call (struct rxrpc_sock*,struct rxrpc_call*,struct rxrpc_conn_parameters*,struct sockaddr_rxrpc*,int /*<<< orphan*/ ) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 

int rxrpc_kernel_retry_call(struct socket *sock, struct rxrpc_call *call,
			    struct sockaddr_rxrpc *srx, struct key *key)
{
	struct rxrpc_conn_parameters cp;
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);
	int ret;

	_enter("%d{%d}", call->debug_id, atomic_read(&call->usage));

	if (!key)
		key = rx->key;
	if (key && !key->payload.data[0])
		key = NULL; /* a no-security key */

	memset(&cp, 0, sizeof(cp));
	cp.local		= rx->local;
	cp.key			= key;
	cp.security_level	= 0;
	cp.exclusive		= false;
	cp.service_id		= srx->srx_service;

	mutex_lock(&call->user_mutex);

	ret = rxrpc_prepare_call_for_retry(rx, call);
	if (ret == 0)
		ret = rxrpc_retry_client_call(rx, call, &cp, srx, GFP_KERNEL);

	mutex_unlock(&call->user_mutex);
	rxrpc_put_peer(cp.peer);
	_leave(" = %d", ret);
	return ret;
}