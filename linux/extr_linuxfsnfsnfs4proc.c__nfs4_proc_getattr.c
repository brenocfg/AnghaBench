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
struct rpc_message {struct nfs4_getattr_res* rpc_resp; struct nfs4_getattr_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct nfs4_getattr_res {int /*<<< orphan*/  seq_res; struct nfs_server* server; struct nfs4_label* label; struct nfs_fattr* fattr; } ;
struct nfs4_getattr_arg {int /*<<< orphan*/  seq_args; int /*<<< orphan*/ * bitmask; struct nfs_fh* fh; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int NFS4_BITMASK_SZ ; 
 size_t NFSPROC4_CLNT_GETATTR ; 
 int /*<<< orphan*/  nfs4_bitmap_copy_adjust (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  nfs4_bitmask (struct nfs_server*,struct nfs4_label*) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 

__attribute__((used)) static int _nfs4_proc_getattr(struct nfs_server *server, struct nfs_fh *fhandle,
				struct nfs_fattr *fattr, struct nfs4_label *label,
				struct inode *inode)
{
	__u32 bitmask[NFS4_BITMASK_SZ];
	struct nfs4_getattr_arg args = {
		.fh = fhandle,
		.bitmask = bitmask,
	};
	struct nfs4_getattr_res res = {
		.fattr = fattr,
		.label = label,
		.server = server,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GETATTR],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	nfs4_bitmap_copy_adjust(bitmask, nfs4_bitmask(server, label), inode);

	nfs_fattr_init(fattr);
	return nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
}