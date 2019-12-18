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
struct dlm_lspace_params {int flags; int /*<<< orphan*/  minor; } ;
struct dlm_ls {int /*<<< orphan*/ * ls_local_handle; } ;
typedef  int /*<<< orphan*/  dlm_lockspace_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int DLM_USER_LSFLG_FORCEFREE ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct dlm_ls* dlm_find_lockspace_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int dlm_release_lockspace (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int device_remove_lockspace(struct dlm_lspace_params *params)
{
	dlm_lockspace_t *lockspace;
	struct dlm_ls *ls;
	int error, force = 0;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	ls = dlm_find_lockspace_device(params->minor);
	if (!ls)
		return -ENOENT;

	if (params->flags & DLM_USER_LSFLG_FORCEFREE)
		force = 2;

	lockspace = ls->ls_local_handle;
	dlm_put_lockspace(ls);

	/* The final dlm_release_lockspace waits for references to go to
	   zero, so all processes will need to close their device for the
	   ls before the release will proceed.  release also calls the
	   device_deregister above.  Converting a positive return value
	   from release to zero means that userspace won't know when its
	   release was the final one, but it shouldn't need to know. */

	error = dlm_release_lockspace(lockspace, force);
	if (error > 0)
		error = 0;
	return error;
}