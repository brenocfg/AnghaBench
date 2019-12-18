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
struct dlm_user_proc {int /*<<< orphan*/  lockspace; } ;
struct dlm_user_args {int /*<<< orphan*/  castaddr; int /*<<< orphan*/  castparam; int /*<<< orphan*/  user_lksb; struct dlm_user_proc* proc; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lock_params {int flags; int /*<<< orphan*/  lvb; int /*<<< orphan*/  lkid; int /*<<< orphan*/  castaddr; int /*<<< orphan*/  castparam; int /*<<< orphan*/  lksb; } ;

/* Variables and functions */
 int DLM_LKF_CANCEL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int dlm_user_cancel (struct dlm_ls*,struct dlm_user_args*,int,int /*<<< orphan*/ ) ; 
 int dlm_user_unlock (struct dlm_ls*,struct dlm_user_args*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dlm_user_args* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_user_unlock(struct dlm_user_proc *proc,
			      struct dlm_lock_params *params)
{
	struct dlm_ls *ls;
	struct dlm_user_args *ua;
	int error = -ENOMEM;

	ls = dlm_find_lockspace_local(proc->lockspace);
	if (!ls)
		return -ENOENT;

	ua = kzalloc(sizeof(struct dlm_user_args), GFP_NOFS);
	if (!ua)
		goto out;
	ua->proc = proc;
	ua->user_lksb = params->lksb;
	ua->castparam = params->castparam;
	ua->castaddr = params->castaddr;

	if (params->flags & DLM_LKF_CANCEL)
		error = dlm_user_cancel(ls, ua, params->flags, params->lkid);
	else
		error = dlm_user_unlock(ls, ua, params->flags, params->lkid,
					params->lvb);
 out:
	dlm_put_lockspace(ls);
	return error;
}