#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_lock_context {int dummy; } ;
struct inode {int dummy; } ;
struct file_lock {int fl_flags; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_4__ {int (* lock ) (struct file*,int,struct file_lock*) ;} ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int FL_CLOSE ; 
 int /*<<< orphan*/  IS_ERR (struct nfs_lock_context*) ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int locks_lock_file_wait (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 struct nfs_lock_context* nfs_get_lock_context (int /*<<< orphan*/ ) ; 
 int nfs_iocounter_wait (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  nfs_put_lock_context (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  nfs_wb_all (struct inode*) ; 
 int stub1 (struct file*,int,struct file_lock*) ; 

__attribute__((used)) static int
do_unlk(struct file *filp, int cmd, struct file_lock *fl, int is_local)
{
	struct inode *inode = filp->f_mapping->host;
	struct nfs_lock_context *l_ctx;
	int status;

	/*
	 * Flush all pending writes before doing anything
	 * with locks..
	 */
	nfs_wb_all(inode);

	l_ctx = nfs_get_lock_context(nfs_file_open_context(filp));
	if (!IS_ERR(l_ctx)) {
		status = nfs_iocounter_wait(l_ctx);
		nfs_put_lock_context(l_ctx);
		/*  NOTE: special case
		 * 	If we're signalled while cleaning up locks on process exit, we
		 * 	still need to complete the unlock.
		 */
		if (status < 0 && !(fl->fl_flags & FL_CLOSE))
			return status;
	}

	/*
	 * Use local locking if mounted with "-onolock" or with appropriate
	 * "-olocal_lock="
	 */
	if (!is_local)
		status = NFS_PROTO(inode)->lock(filp, cmd, fl);
	else
		status = locks_lock_file_wait(filp, fl);
	return status;
}