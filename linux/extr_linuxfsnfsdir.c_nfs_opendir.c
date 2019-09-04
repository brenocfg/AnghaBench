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
struct rpc_cred {int dummy; } ;
typedef  struct rpc_cred nfs_open_dir_context ;
struct inode {int dummy; } ;
struct file {struct rpc_cred* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 scalar_t__ IS_ERR (struct rpc_cred*) ; 
 int /*<<< orphan*/  NFSIOS_VFSOPEN ; 
 int PTR_ERR (struct rpc_cred*) ; 
 struct rpc_cred* alloc_nfs_open_dir_context (struct inode*,struct rpc_cred*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_rpccred (struct rpc_cred*) ; 
 struct rpc_cred* rpc_lookup_cred () ; 

__attribute__((used)) static int
nfs_opendir(struct inode *inode, struct file *filp)
{
	int res = 0;
	struct nfs_open_dir_context *ctx;
	struct rpc_cred *cred;

	dfprintk(FILE, "NFS: open dir(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);

	cred = rpc_lookup_cred();
	if (IS_ERR(cred))
		return PTR_ERR(cred);
	ctx = alloc_nfs_open_dir_context(inode, cred);
	if (IS_ERR(ctx)) {
		res = PTR_ERR(ctx);
		goto out;
	}
	filp->private_data = ctx;
out:
	put_rpccred(cred);
	return res;
}