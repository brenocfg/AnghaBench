#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {TYPE_6__* rpc_resp; TYPE_5__* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  s_dev; TYPE_2__* nfs_client; } ;
struct TYPE_12__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_dev; int /*<<< orphan*/  id; int /*<<< orphan*/  clientid; } ;
struct TYPE_11__ {int /*<<< orphan*/  seq_args; TYPE_4__ lock_owner; } ;
struct nfs_release_lockowner_data {TYPE_6__ res; TYPE_5__ args; struct nfs_server* server; struct nfs4_lock_state* lsp; } ;
struct TYPE_9__ {int /*<<< orphan*/  owner_id; } ;
struct nfs4_lock_state {TYPE_3__ ls_seqid; } ;
struct TYPE_8__ {int /*<<< orphan*/  cl_clientid; TYPE_1__* cl_mvops; } ;
struct TYPE_7__ {scalar_t__ minor_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t NFSPROC4_CLNT_RELEASE_LOCKOWNER ; 
 struct nfs_release_lockowner_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_release_lockowner_ops ; 
 int /*<<< orphan*/  rpc_call_async (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_release_lockowner_data*) ; 

__attribute__((used)) static void
nfs4_release_lockowner(struct nfs_server *server, struct nfs4_lock_state *lsp)
{
	struct nfs_release_lockowner_data *data;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RELEASE_LOCKOWNER],
	};

	if (server->nfs_client->cl_mvops->minor_version != 0)
		return;

	data = kmalloc(sizeof(*data), GFP_NOFS);
	if (!data)
		return;
	data->lsp = lsp;
	data->server = server;
	data->args.lock_owner.clientid = server->nfs_client->cl_clientid;
	data->args.lock_owner.id = lsp->ls_seqid.owner_id;
	data->args.lock_owner.s_dev = server->s_dev;

	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0, 0);
	rpc_call_async(server->client, &msg, 0, &nfs4_release_lockowner_ops, data);
}