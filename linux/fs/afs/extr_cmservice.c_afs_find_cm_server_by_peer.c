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
struct afs_server {int dummy; } ;
struct afs_call {struct afs_server* server; TYPE_1__* net; int /*<<< orphan*/  rxcall; } ;
struct TYPE_2__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 struct afs_server* afs_find_server (TYPE_1__*,struct sockaddr_rxrpc*) ; 
 int afs_record_cm_probe (struct afs_call*,struct afs_server*) ; 
 int /*<<< orphan*/  rxrpc_kernel_get_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr_rxrpc*) ; 
 int /*<<< orphan*/  trace_afs_cm_no_server (struct afs_call*,struct sockaddr_rxrpc*) ; 

__attribute__((used)) static int afs_find_cm_server_by_peer(struct afs_call *call)
{
	struct sockaddr_rxrpc srx;
	struct afs_server *server;

	rxrpc_kernel_get_peer(call->net->socket, call->rxcall, &srx);

	server = afs_find_server(call->net, &srx);
	if (!server) {
		trace_afs_cm_no_server(call, &srx);
		return 0;
	}

	call->server = server;
	return afs_record_cm_probe(call, server);
}