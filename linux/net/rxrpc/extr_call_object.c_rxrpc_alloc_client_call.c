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
struct sockaddr_rxrpc {int /*<<< orphan*/  srx_service; } ;
struct rxrpc_sock {int dummy; } ;
struct rxrpc_call {int tx_phase; void* cong_tstamp; void* acks_latest_ts; int /*<<< orphan*/  service_id; int /*<<< orphan*/  state; } ;
typedef  void* ktime_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rxrpc_call* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RXRPC_CALL_CLIENT_AWAIT_CONN ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_call*) ; 
 void* ktime_get_real () ; 
 struct rxrpc_call* rxrpc_alloc_call (struct rxrpc_sock*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct rxrpc_call *rxrpc_alloc_client_call(struct rxrpc_sock *rx,
						  struct sockaddr_rxrpc *srx,
						  gfp_t gfp,
						  unsigned int debug_id)
{
	struct rxrpc_call *call;
	ktime_t now;

	_enter("");

	call = rxrpc_alloc_call(rx, gfp, debug_id);
	if (!call)
		return ERR_PTR(-ENOMEM);
	call->state = RXRPC_CALL_CLIENT_AWAIT_CONN;
	call->service_id = srx->srx_service;
	call->tx_phase = true;
	now = ktime_get_real();
	call->acks_latest_ts = now;
	call->cong_tstamp = now;

	_leave(" = %p", call);
	return call;
}