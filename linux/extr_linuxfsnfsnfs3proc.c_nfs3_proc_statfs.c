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
struct rpc_message {struct nfs_fsstat* rpc_resp; struct nfs_fh* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fsstat {int /*<<< orphan*/  fattr; } ;
struct nfs_fh {int dummy; } ;

/* Variables and functions */
 size_t NFS3PROC_FSSTAT ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_proc_statfs(struct nfs_server *server, struct nfs_fh *fhandle,
		 struct nfs_fsstat *stat)
{
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_FSSTAT],
		.rpc_argp	= fhandle,
		.rpc_resp	= stat,
	};
	int	status;

	dprintk("NFS call  fsstat\n");
	nfs_fattr_init(stat->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprintk("NFS reply fsstat: %d\n", status);
	return status;
}