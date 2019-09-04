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
struct sockaddr_rxrpc {int dummy; } ;
struct afs_call {int /*<<< orphan*/  cm_server; TYPE_1__* net; int /*<<< orphan*/  rxcall; } ;
struct TYPE_2__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_find_server (TYPE_1__*,struct sockaddr_rxrpc*) ; 
 int afs_queue_call_work (struct afs_call*) ; 
 int /*<<< orphan*/  rxrpc_kernel_get_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_rxrpc*) ; 
 int /*<<< orphan*/  trace_afs_cm_no_server (struct afs_call*,struct sockaddr_rxrpc*) ; 

__attribute__((used)) static int afs_deliver_cb_init_call_back_state(struct afs_call *call)
{
	struct sockaddr_rxrpc srx;
	int ret;

	_enter("");

	rxrpc_kernel_get_peer(call->net->socket, call->rxcall, &srx);

	ret = afs_extract_data(call, NULL, 0, false);
	if (ret < 0)
		return ret;

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	call->cm_server = afs_find_server(call->net, &srx);
	if (!call->cm_server)
		trace_afs_cm_no_server(call, &srx);

	return afs_queue_call_work(call);
}