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
struct rpc_message {struct nfs_fattr* rpc_resp; struct nfs_fh* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC_GETATTR ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_getattr(struct nfs_server *server, struct nfs_fh *fhandle,
		struct nfs_fattr *fattr, struct nfs4_label *label,
		struct inode *inode)
{
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_GETATTR],
		.rpc_argp	= fhandle,
		.rpc_resp	= fattr,
	};
	int	status;

	dprintk("NFS call  getattr\n");
	nfs_fattr_init(fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprintk("NFS reply getattr: %d\n", status);
	return status;
}