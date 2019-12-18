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
struct nfs_open_dir_context {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct nfs_open_dir_context* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 scalar_t__ IS_ERR (struct nfs_open_dir_context*) ; 
 int /*<<< orphan*/  NFSIOS_VFSOPEN ; 
 int PTR_ERR (struct nfs_open_dir_context*) ; 
 struct nfs_open_dir_context* alloc_nfs_open_dir_context (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_opendir(struct inode *inode, struct file *filp)
{
	int res = 0;
	struct nfs_open_dir_context *ctx;

	dfprintk(FILE, "NFS: open dir(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);

	ctx = alloc_nfs_open_dir_context(inode, current_cred());
	if (IS_ERR(ctx)) {
		res = PTR_ERR(ctx);
		goto out;
	}
	filp->private_data = ctx;
out:
	return res;
}