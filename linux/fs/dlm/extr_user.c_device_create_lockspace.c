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
struct dlm_lspace_params {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int minor; } ;
struct dlm_ls {TYPE_1__ ls_device; } ;
typedef  int /*<<< orphan*/  dlm_lockspace_t ;
struct TYPE_4__ {int /*<<< orphan*/  ci_cluster_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  DLM_USER_LVB_LEN ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__ dlm_config ; 
 int dlm_device_register (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ *) ; 
 int dlm_new_lockspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int device_create_lockspace(struct dlm_lspace_params *params)
{
	dlm_lockspace_t *lockspace;
	struct dlm_ls *ls;
	int error;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	error = dlm_new_lockspace(params->name, dlm_config.ci_cluster_name, params->flags,
				  DLM_USER_LVB_LEN, NULL, NULL, NULL,
				  &lockspace);
	if (error)
		return error;

	ls = dlm_find_lockspace_local(lockspace);
	if (!ls)
		return -ENOENT;

	error = dlm_device_register(ls, params->name);
	dlm_put_lockspace(ls);

	if (error)
		dlm_release_lockspace(lockspace, 0);
	else
		error = ls->ls_device.minor;

	return error;
}