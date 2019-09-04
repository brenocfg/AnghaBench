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
typedef  int uint32_t ;
struct dlm_user_proc {int /*<<< orphan*/  lockspace; } ;
struct TYPE_2__ {int sb_lkid; } ;
struct dlm_user_args {TYPE_1__ lksb; int /*<<< orphan*/  xid; int /*<<< orphan*/  bastaddr; int /*<<< orphan*/  bastparam; scalar_t__ castaddr; int /*<<< orphan*/  castparam; scalar_t__ user_lksb; struct dlm_user_proc* proc; } ;
struct dlm_ls {int dummy; } ;
struct dlm_lock_params {int flags; scalar_t__ timeout; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  mode; int /*<<< orphan*/  lvb; int /*<<< orphan*/  lkid; int /*<<< orphan*/  xid; int /*<<< orphan*/  bastaddr; int /*<<< orphan*/  bastparam; scalar_t__ castaddr; int /*<<< orphan*/  castparam; scalar_t__ lksb; } ;

/* Variables and functions */
 int DLM_LKF_CONVERT ; 
 int DLM_LKF_ORPHAN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int dlm_user_adopt_orphan (struct dlm_ls*,struct dlm_user_args*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int*) ; 
 int dlm_user_convert (struct dlm_ls*,struct dlm_user_args*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int dlm_user_request (struct dlm_ls*,struct dlm_user_args*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct dlm_user_args* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_user_lock(struct dlm_user_proc *proc,
			    struct dlm_lock_params *params)
{
	struct dlm_ls *ls;
	struct dlm_user_args *ua;
	uint32_t lkid;
	int error = -ENOMEM;

	ls = dlm_find_lockspace_local(proc->lockspace);
	if (!ls)
		return -ENOENT;

	if (!params->castaddr || !params->lksb) {
		error = -EINVAL;
		goto out;
	}

	ua = kzalloc(sizeof(struct dlm_user_args), GFP_NOFS);
	if (!ua)
		goto out;
	ua->proc = proc;
	ua->user_lksb = params->lksb;
	ua->castparam = params->castparam;
	ua->castaddr = params->castaddr;
	ua->bastparam = params->bastparam;
	ua->bastaddr = params->bastaddr;
	ua->xid = params->xid;

	if (params->flags & DLM_LKF_CONVERT) {
		error = dlm_user_convert(ls, ua,
				         params->mode, params->flags,
				         params->lkid, params->lvb,
					 (unsigned long) params->timeout);
	} else if (params->flags & DLM_LKF_ORPHAN) {
		error = dlm_user_adopt_orphan(ls, ua,
					 params->mode, params->flags,
					 params->name, params->namelen,
					 (unsigned long) params->timeout,
					 &lkid);
		if (!error)
			error = lkid;
	} else {
		error = dlm_user_request(ls, ua,
					 params->mode, params->flags,
					 params->name, params->namelen,
					 (unsigned long) params->timeout);
		if (!error)
			error = ua->lksb.sb_lkid;
	}
 out:
	dlm_put_lockspace(ls);
	return error;
}