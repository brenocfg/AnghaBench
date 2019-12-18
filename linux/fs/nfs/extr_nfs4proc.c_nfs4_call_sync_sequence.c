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
struct rpc_task_setup {struct nfs4_call_sync_data* callback_data; int /*<<< orphan*/  callback_ops; struct rpc_message* rpc_message; struct rpc_clnt* rpc_client; } ;
struct rpc_message {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {TYPE_1__* cl_mvops; } ;
struct nfs4_sequence_res {int dummy; } ;
struct nfs4_sequence_args {int dummy; } ;
struct nfs4_call_sync_data {struct nfs4_sequence_res* seq_res; struct nfs4_sequence_args* seq_args; struct nfs_server* seq_server; } ;
struct TYPE_2__ {int /*<<< orphan*/  call_sync_ops; } ;

/* Variables and functions */
 int nfs4_call_sync_custom (struct rpc_task_setup*) ; 

__attribute__((used)) static int nfs4_call_sync_sequence(struct rpc_clnt *clnt,
				   struct nfs_server *server,
				   struct rpc_message *msg,
				   struct nfs4_sequence_args *args,
				   struct nfs4_sequence_res *res)
{
	struct nfs_client *clp = server->nfs_client;
	struct nfs4_call_sync_data data = {
		.seq_server = server,
		.seq_args = args,
		.seq_res = res,
	};
	struct rpc_task_setup task_setup = {
		.rpc_client = clnt,
		.rpc_message = msg,
		.callback_ops = clp->cl_mvops->call_sync_ops,
		.callback_data = &data
	};

	return nfs4_call_sync_custom(&task_setup);
}