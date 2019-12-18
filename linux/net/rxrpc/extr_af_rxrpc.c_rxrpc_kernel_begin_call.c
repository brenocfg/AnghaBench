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
struct rxrpc_sock {int /*<<< orphan*/  min_sec_level; int /*<<< orphan*/  local; struct key* key; int /*<<< orphan*/  sk; } ;
struct rxrpc_conn_parameters {unsigned long user_call_ID; int intr; int exclusive; int upgrade; int /*<<< orphan*/  peer; int /*<<< orphan*/  service_id; int /*<<< orphan*/  security_level; struct key* key; int /*<<< orphan*/  local; int /*<<< orphan*/  tx_total_len; } ;
struct rxrpc_call_params {unsigned long user_call_ID; int intr; int exclusive; int upgrade; int /*<<< orphan*/  peer; int /*<<< orphan*/  service_id; int /*<<< orphan*/  security_level; struct key* key; int /*<<< orphan*/  local; int /*<<< orphan*/  tx_total_len; } ;
struct rxrpc_call {int /*<<< orphan*/  user_mutex; int /*<<< orphan*/  notify_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  rxrpc_notify_rx_t ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 struct rxrpc_call* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct rxrpc_call*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_call*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rxrpc_conn_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rxrpc_call* rxrpc_new_client_call (struct rxrpc_sock*,struct rxrpc_conn_parameters*,struct sockaddr_rxrpc*,struct rxrpc_conn_parameters*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rxrpc_put_peer (int /*<<< orphan*/ ) ; 
 struct rxrpc_sock* rxrpc_sk (int /*<<< orphan*/ ) ; 
 int rxrpc_validate_address (struct rxrpc_sock*,struct sockaddr_rxrpc*,int) ; 

struct rxrpc_call *rxrpc_kernel_begin_call(struct socket *sock,
					   struct sockaddr_rxrpc *srx,
					   struct key *key,
					   unsigned long user_call_ID,
					   s64 tx_total_len,
					   gfp_t gfp,
					   rxrpc_notify_rx_t notify_rx,
					   bool upgrade,
					   bool intr,
					   unsigned int debug_id)
{
	struct rxrpc_conn_parameters cp;
	struct rxrpc_call_params p;
	struct rxrpc_call *call;
	struct rxrpc_sock *rx = rxrpc_sk(sock->sk);
	int ret;

	_enter(",,%x,%lx", key_serial(key), user_call_ID);

	ret = rxrpc_validate_address(rx, srx, sizeof(*srx));
	if (ret < 0)
		return ERR_PTR(ret);

	lock_sock(&rx->sk);

	if (!key)
		key = rx->key;
	if (key && !key->payload.data[0])
		key = NULL; /* a no-security key */

	memset(&p, 0, sizeof(p));
	p.user_call_ID = user_call_ID;
	p.tx_total_len = tx_total_len;
	p.intr = intr;

	memset(&cp, 0, sizeof(cp));
	cp.local		= rx->local;
	cp.key			= key;
	cp.security_level	= rx->min_sec_level;
	cp.exclusive		= false;
	cp.upgrade		= upgrade;
	cp.service_id		= srx->srx_service;
	call = rxrpc_new_client_call(rx, &cp, srx, &p, gfp, debug_id);
	/* The socket has been unlocked. */
	if (!IS_ERR(call)) {
		call->notify_rx = notify_rx;
		mutex_unlock(&call->user_mutex);
	}

	rxrpc_put_peer(cp.peer);
	_leave(" = %p", call);
	return call;
}