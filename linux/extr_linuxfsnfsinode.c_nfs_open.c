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
struct nfs_open_context {int dummy; } ;
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  f_mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs_open_context*) ; 
 int PTR_ERR (struct nfs_open_context*) ; 
 struct nfs_open_context* alloc_nfs_open_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  file_dentry (struct file*) ; 
 int /*<<< orphan*/  nfs_file_set_open_context (struct file*,struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_fscache_open_file (struct inode*,struct file*) ; 
 int /*<<< orphan*/  put_nfs_open_context (struct nfs_open_context*) ; 

int nfs_open(struct inode *inode, struct file *filp)
{
	struct nfs_open_context *ctx;

	ctx = alloc_nfs_open_context(file_dentry(filp), filp->f_mode, filp);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);
	nfs_file_set_open_context(filp, ctx);
	put_nfs_open_context(ctx);
	nfs_fscache_open_file(inode, filp);
	return 0;
}