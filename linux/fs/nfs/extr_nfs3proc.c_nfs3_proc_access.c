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
struct rpc_message {int /*<<< orphan*/  rpc_cred; struct nfs3_accessres* rpc_resp; struct nfs3_accessargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_access_entry {int /*<<< orphan*/  cred; int /*<<< orphan*/  mask; } ;
struct nfs3_accessres {int /*<<< orphan*/ * fattr; int /*<<< orphan*/  access; } ;
struct nfs3_accessargs {int /*<<< orphan*/  access; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NFS3PROC_ACCESS ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 
 int /*<<< orphan*/  nfs_access_set_mask (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_alloc_fattr () ; 
 int /*<<< orphan*/  nfs_free_fattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs3_proc_access(struct inode *inode, struct nfs_access_entry *entry)
{
	struct nfs3_accessargs	arg = {
		.fh		= NFS_FH(inode),
		.access		= entry->mask,
	};
	struct nfs3_accessres	res;
	struct rpc_message msg = {
		.rpc_proc	= &nfs3_procedures[NFS3PROC_ACCESS],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= entry->cred,
	};
	int status = -ENOMEM;

	dprintk("NFS call  access\n");
	res.fattr = nfs_alloc_fattr();
	if (res.fattr == NULL)
		goto out;

	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_refresh_inode(inode, res.fattr);
	if (status == 0)
		nfs_access_set_mask(entry, res.access);
	nfs_free_fattr(res.fattr);
out:
	dprintk("NFS reply access: %d\n", status);
	return status;
}