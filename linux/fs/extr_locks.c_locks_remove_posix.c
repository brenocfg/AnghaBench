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
struct inode {int /*<<< orphan*/  i_flctx; } ;
struct file_lock_context {int /*<<< orphan*/  flc_posix; } ;
struct file_lock {int fl_flags; TYPE_1__* fl_ops; int /*<<< orphan*/ * fl_lmops; struct file* fl_file; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_owner; int /*<<< orphan*/  fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_type; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_4__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fl_release_private ) (struct file_lock*) ;} ;

/* Variables and functions */
 int FL_CLOSE ; 
 int FL_POSIX ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_2__* current ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 struct inode* locks_inode (struct file*) ; 
 struct file_lock_context* smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct file_lock*) ; 
 int /*<<< orphan*/  trace_locks_remove_posix (struct inode*,struct file_lock*,int) ; 
 int vfs_lock_file (struct file*,int /*<<< orphan*/ ,struct file_lock*,int /*<<< orphan*/ *) ; 

void locks_remove_posix(struct file *filp, fl_owner_t owner)
{
	int error;
	struct inode *inode = locks_inode(filp);
	struct file_lock lock;
	struct file_lock_context *ctx;

	/*
	 * If there are no locks held on this file, we don't need to call
	 * posix_lock_file().  Another process could be setting a lock on this
	 * file at the same time, but we wouldn't remove that lock anyway.
	 */
	ctx =  smp_load_acquire(&inode->i_flctx);
	if (!ctx || list_empty(&ctx->flc_posix))
		return;

	locks_init_lock(&lock);
	lock.fl_type = F_UNLCK;
	lock.fl_flags = FL_POSIX | FL_CLOSE;
	lock.fl_start = 0;
	lock.fl_end = OFFSET_MAX;
	lock.fl_owner = owner;
	lock.fl_pid = current->tgid;
	lock.fl_file = filp;
	lock.fl_ops = NULL;
	lock.fl_lmops = NULL;

	error = vfs_lock_file(filp, F_SETLK, &lock, NULL);

	if (lock.fl_ops && lock.fl_ops->fl_release_private)
		lock.fl_ops->fl_release_private(&lock);
	trace_locks_remove_posix(inode, &lock, error);
}