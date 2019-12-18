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
struct dlm_purge_params {int /*<<< orphan*/  pid; int /*<<< orphan*/  nodeid; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int dlm_user_purge (struct dlm_ls*,struct dlm_user_proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_user_purge(struct dlm_user_proc *proc,
			     struct dlm_purge_params *params)
{
	struct dlm_ls *ls;
	int error;

	ls = dlm_find_lockspace_local(proc->lockspace);
	if (!ls)
		return -ENOENT;

	error = dlm_user_purge(ls, proc, params->nodeid, params->pid);

	dlm_put_lockspace(ls);
	return error;
}