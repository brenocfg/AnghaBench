#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file_lock_context {int /*<<< orphan*/  flc_flock; } ;
struct file_lock {int fl_flags; TYPE_2__* fl_ops; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_type; struct file* fl_file; int /*<<< orphan*/  fl_pid; struct file* fl_owner; } ;
struct file {TYPE_1__* f_op; } ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fl_release_private ) (struct file_lock*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* flock ) (struct file*,int /*<<< orphan*/ ,struct file_lock*) ;} ;

/* Variables and functions */
 int FL_CLOSE ; 
 int FL_FLOCK ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  flock_lock_inode (struct inode*,struct file_lock*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct inode* locks_inode (struct file*) ; 
 int /*<<< orphan*/  stub1 (struct file*,int /*<<< orphan*/ ,struct file_lock*) ; 
 int /*<<< orphan*/  stub2 (struct file_lock*) ; 

__attribute__((used)) static void
locks_remove_flock(struct file *filp, struct file_lock_context *flctx)
{
	struct file_lock fl = {
		.fl_owner = filp,
		.fl_pid = current->tgid,
		.fl_file = filp,
		.fl_flags = FL_FLOCK | FL_CLOSE,
		.fl_type = F_UNLCK,
		.fl_end = OFFSET_MAX,
	};
	struct inode *inode = locks_inode(filp);

	if (list_empty(&flctx->flc_flock))
		return;

	if (filp->f_op->flock)
		filp->f_op->flock(filp, F_SETLKW, &fl);
	else
		flock_lock_inode(inode, &fl);

	if (fl.fl_ops && fl.fl_ops->fl_release_private)
		fl.fl_ops->fl_release_private(&fl);
}