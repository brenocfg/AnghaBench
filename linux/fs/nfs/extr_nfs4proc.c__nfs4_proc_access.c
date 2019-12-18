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
struct rpc_message {int /*<<< orphan*/  rpc_cred; struct nfs4_accessres* rpc_resp; struct nfs4_accessargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  cache_consistency_bitmask; } ;
struct nfs_access_entry {int /*<<< orphan*/  cred; int /*<<< orphan*/  mask; } ;
struct nfs4_accessres {int /*<<< orphan*/ * fattr; int /*<<< orphan*/  access; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs4_accessargs {int /*<<< orphan*/  seq_args; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  access; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FMODE_READ ; 
 size_t NFSPROC4_CLNT_ACCESS ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_have_delegation (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_access_set_mask (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nfs4_proc_access(struct inode *inode, struct nfs_access_entry *entry)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs4_accessargs args = {
		.fh = NFS_FH(inode),
		.access = entry->mask,
	};
	struct nfs4_accessres res = {
		.server = server,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_ACCESS],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = entry->cred,
	};
	int status = 0;

	if (!nfs4_have_delegation(inode, FMODE_READ)) {
		res.fattr = nfs_alloc_fattr();
		if (res.fattr == NULL)
			return -ENOMEM;
		args.bitmask = server->cache_consistency_bitmask;
	}
	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	if (!status) {
		nfs_access_set_mask(entry, res.access);
		if (res.fattr)
			nfs_refresh_inode(inode, res.fattr);
	}
	nfs_free_fattr(res.fattr);
	return status;
}