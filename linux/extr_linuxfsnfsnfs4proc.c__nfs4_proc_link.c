#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {struct nfs4_link_res* rpc_resp; struct nfs4_link_arg* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs4_link_res {TYPE_1__* fattr; int /*<<< orphan*/ * label; int /*<<< orphan*/  cinfo; int /*<<< orphan*/  seq_res; struct nfs_server* server; } ;
struct nfs4_link_arg {int /*<<< orphan*/  seq_args; int /*<<< orphan*/ * bitmask; struct qstr const* name; int /*<<< orphan*/  dir_fh; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_5__ {int /*<<< orphan*/  time_start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int NFS4_BITMASK_SZ ; 
 size_t NFSPROC4_CLNT_LINK ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_bitmap_copy_adjust_setattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  nfs4_bitmask (struct nfs_server*,int /*<<< orphan*/ *) ; 
 int nfs4_call_sync (int /*<<< orphan*/ ,struct nfs_server*,struct rpc_message*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_inode_make_writeable (struct inode*) ; 
 int /*<<< orphan*/ * nfs4_label_alloc (struct nfs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_label_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 TYPE_1__* nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (TYPE_1__*) ; 
 int nfs_post_op_update_inode (struct inode*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_setsecurity (struct inode*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _nfs4_proc_link(struct inode *inode, struct inode *dir, const struct qstr *name)
{
	struct nfs_server *server = NFS_SERVER(inode);
	__u32 bitmask[NFS4_BITMASK_SZ];
	struct nfs4_link_arg arg = {
		.fh     = NFS_FH(inode),
		.dir_fh = NFS_FH(dir),
		.name   = name,
		.bitmask = bitmask,
	};
	struct nfs4_link_res res = {
		.server = server,
		.label = NULL,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LINK],
		.rpc_argp = &arg,
		.rpc_resp = &res,
	};
	int status = -ENOMEM;

	res.fattr = nfs_alloc_fattr();
	if (res.fattr == NULL)
		goto out;

	res.label = nfs4_label_alloc(server, GFP_KERNEL);
	if (IS_ERR(res.label)) {
		status = PTR_ERR(res.label);
		goto out;
	}

	nfs4_inode_make_writeable(inode);
	nfs4_bitmap_copy_adjust_setattr(bitmask, nfs4_bitmask(server, res.label), inode);

	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	if (!status) {
		update_changeattr(dir, &res.cinfo, res.fattr->time_start, 0);
		status = nfs_post_op_update_inode(inode, res.fattr);
		if (!status)
			nfs_setsecurity(inode, res.fattr, res.label);
	}


	nfs4_label_free(res.label);

out:
	nfs_free_fattr(res.fattr);
	return status;
}