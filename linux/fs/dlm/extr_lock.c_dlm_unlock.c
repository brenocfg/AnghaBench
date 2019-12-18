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
typedef  int uint32_t ;
struct dlm_ls {int dummy; } ;
struct dlm_lksb {int dummy; } ;
struct dlm_lkb {int dummy; } ;
struct dlm_args {int dummy; } ;
typedef  int /*<<< orphan*/  dlm_lockspace_t ;

/* Variables and functions */
 int DLM_ECANCEL ; 
 int DLM_EUNLOCK ; 
 int DLM_LKF_CANCEL ; 
 int DLM_LKF_FORCEUNLOCK ; 
 int EBUSY ; 
 int EINVAL ; 
 int cancel_lock (struct dlm_ls*,struct dlm_lkb*,struct dlm_args*) ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lock_recovery (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_put_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_unlock_recovery (struct dlm_ls*) ; 
 int find_lkb (struct dlm_ls*,int,struct dlm_lkb**) ; 
 int set_unlock_args (int,void*,struct dlm_args*) ; 
 int unlock_lock (struct dlm_ls*,struct dlm_lkb*,struct dlm_args*) ; 

int dlm_unlock(dlm_lockspace_t *lockspace,
	       uint32_t lkid,
	       uint32_t flags,
	       struct dlm_lksb *lksb,
	       void *astarg)
{
	struct dlm_ls *ls;
	struct dlm_lkb *lkb;
	struct dlm_args args;
	int error;

	ls = dlm_find_lockspace_local(lockspace);
	if (!ls)
		return -EINVAL;

	dlm_lock_recovery(ls);

	error = find_lkb(ls, lkid, &lkb);
	if (error)
		goto out;

	error = set_unlock_args(flags, astarg, &args);
	if (error)
		goto out_put;

	if (flags & DLM_LKF_CANCEL)
		error = cancel_lock(ls, lkb, &args);
	else
		error = unlock_lock(ls, lkb, &args);

	if (error == -DLM_EUNLOCK || error == -DLM_ECANCEL)
		error = 0;
	if (error == -EBUSY && (flags & (DLM_LKF_CANCEL | DLM_LKF_FORCEUNLOCK)))
		error = 0;
 out_put:
	dlm_put_lkb(lkb);
 out:
	dlm_unlock_recovery(ls);
	dlm_put_lockspace(ls);
	return error;
}