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
struct rpc_message {struct nfs_diropok* rpc_resp; struct nfs_diropargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct qstr {int name; int /*<<< orphan*/  len; } ;
struct nfs_fh {int dummy; } ;
struct nfs_fattr {int dummy; } ;
struct nfs_diropok {struct nfs_fattr* fattr; struct nfs_fh* fh; } ;
struct nfs_diropargs {int name; int /*<<< orphan*/  len; int /*<<< orphan*/  fh; } ;
struct nfs4_label {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC_LOOKUP ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  nfs_fattr_init (struct nfs_fattr*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_lookup(struct inode *dir, const struct qstr *name,
		struct nfs_fh *fhandle, struct nfs_fattr *fattr,
		struct nfs4_label *label)
{
	struct nfs_diropargs	arg = {
		.fh		= NFS_FH(dir),
		.name		= name->name,
		.len		= name->len
	};
	struct nfs_diropok	res = {
		.fh		= fhandle,
		.fattr		= fattr
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_LOOKUP],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	};
	int			status;

	dprintk("NFS call  lookup %s\n", name->name);
	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	dprintk("NFS reply lookup: %d\n", status);
	return status;
}