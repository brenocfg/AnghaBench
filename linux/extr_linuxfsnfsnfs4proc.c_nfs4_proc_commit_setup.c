#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  nfs_client; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq_args; } ;
struct nfs_commit_data {TYPE_2__ res; TYPE_1__ args; int /*<<< orphan*/ * commit_done_cb; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_COMMIT ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_SP4_MACH_CRED_COMMIT ; 
 int /*<<< orphan*/ * nfs4_commit_done_cb ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_state_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpc_clnt**,struct rpc_message*) ; 

__attribute__((used)) static void nfs4_proc_commit_setup(struct nfs_commit_data *data, struct rpc_message *msg,
				   struct rpc_clnt **clnt)
{
	struct nfs_server *server = NFS_SERVER(data->inode);

	if (data->commit_done_cb == NULL)
		data->commit_done_cb = nfs4_commit_done_cb;
	data->res.server = server;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COMMIT];
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1, 0);
	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_COMMIT, clnt, msg);
}