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
struct inode {int dummy; } ;
struct file {struct dlm_user_proc* private_data; } ;
struct dlm_user_proc {int /*<<< orphan*/  wait; int /*<<< orphan*/  locks_spin; int /*<<< orphan*/  asts_spin; int /*<<< orphan*/  unlocking; int /*<<< orphan*/  locks; int /*<<< orphan*/  asts; int /*<<< orphan*/  lockspace; } ;
struct dlm_ls {int /*<<< orphan*/  ls_local_handle; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dlm_ls* dlm_find_lockspace_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct dlm_user_proc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_open(struct inode *inode, struct file *file)
{
	struct dlm_user_proc *proc;
	struct dlm_ls *ls;

	ls = dlm_find_lockspace_device(iminor(inode));
	if (!ls)
		return -ENOENT;

	proc = kzalloc(sizeof(struct dlm_user_proc), GFP_NOFS);
	if (!proc) {
		dlm_put_lockspace(ls);
		return -ENOMEM;
	}

	proc->lockspace = ls->ls_local_handle;
	INIT_LIST_HEAD(&proc->asts);
	INIT_LIST_HEAD(&proc->locks);
	INIT_LIST_HEAD(&proc->unlocking);
	spin_lock_init(&proc->asts_spin);
	spin_lock_init(&proc->locks_spin);
	init_waitqueue_head(&proc->wait);
	file->private_data = proc;

	return 0;
}