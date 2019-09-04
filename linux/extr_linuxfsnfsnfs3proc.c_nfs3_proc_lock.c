#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_open_context {int /*<<< orphan*/  flags; } ;
struct nfs_lock_context {int dummy; } ;
struct inode {int dummy; } ;
struct file_lock {int fl_flags; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlm_host; } ;

/* Variables and functions */
 int FL_CLOSE ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  NFS_CONTEXT_UNLOCK ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 struct nfs_open_context* nfs_file_open_context (struct file*) ; 
 struct nfs_lock_context* nfs_get_lock_context (struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 
 int nlmclnt_proc (int /*<<< orphan*/ ,int,struct file_lock*,struct nfs_lock_context*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs3_proc_lock(struct file *filp, int cmd, struct file_lock *fl)
{
	struct inode *inode = file_inode(filp);
	struct nfs_lock_context *l_ctx = NULL;
	struct nfs_open_context *ctx = nfs_file_open_context(filp);
	int status;

	if (fl->fl_flags & FL_CLOSE) {
		l_ctx = nfs_get_lock_context(ctx);
		if (IS_ERR(l_ctx))
			l_ctx = NULL;
		else
			set_bit(NFS_CONTEXT_UNLOCK, &ctx->flags);
	}

	status = nlmclnt_proc(NFS_SERVER(inode)->nlm_host, cmd, fl, l_ctx);

	if (l_ctx)
		nfs_put_lock_context(l_ctx);

	return status;
}