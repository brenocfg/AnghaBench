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
struct rpc_message {struct nfs_removeargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_removeargs {int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 size_t NFSPROC_REMOVE ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_remove(struct inode *dir, struct dentry *dentry)
{
	struct nfs_removeargs arg = {
		.fh = NFS_FH(dir),
		.name = dentry->d_name,
	};
	struct rpc_message msg = { 
		.rpc_proc = &nfs_procedures[NFSPROC_REMOVE],
		.rpc_argp = &arg,
	};
	int			status;

	dprintk("NFS call  remove %pd2\n",dentry);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_for_revalidate(dir);

	dprintk("NFS reply remove: %d\n", status);
	return status;
}