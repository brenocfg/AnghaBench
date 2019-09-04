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
struct rpc_message {struct nfs_commitres* rpc_resp; struct nfs_commitargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_commitres {int /*<<< orphan*/  seq_res; } ;
struct nfs_commitargs {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_COMMIT ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 

__attribute__((used)) static int _nfs4_proc_commit(struct file *dst, struct nfs_commitargs *args,
				struct nfs_commitres *res)
{
	struct inode *dst_inode = file_inode(dst);
	struct nfs_server *server = NFS_SERVER(dst_inode);
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COMMIT],
		.rpc_argp = args,
		.rpc_resp = res,
	};

	args->fh = NFS_FH(dst_inode);
	return nfs4_call_sync(server->client, server, &msg,
			&args->seq_args, &res->seq_res, 1);
}