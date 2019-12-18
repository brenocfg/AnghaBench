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
struct task_struct {int dummy; } ;
struct rlimit {int /*<<< orphan*/  rlim_max; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_OPT_NOAUDIT ; 
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  __task_cred (struct task_struct*) ; 
 scalar_t__ aa_capable (struct aa_label*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aa_label* aa_get_newest_cred_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  audit_resource (struct aa_profile*,unsigned int,int /*<<< orphan*/ ,struct aa_label*,char*,int /*<<< orphan*/ ) ; 
 int fn_for_each (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_setrlimit (struct aa_profile*,unsigned int,struct rlimit*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int aa_task_setrlimit(struct aa_label *label, struct task_struct *task,
		      unsigned int resource, struct rlimit *new_rlim)
{
	struct aa_profile *profile;
	struct aa_label *peer;
	int error = 0;

	rcu_read_lock();
	peer = aa_get_newest_cred_label(__task_cred(task));
	rcu_read_unlock();

	/* TODO: extend resource control to handle other (non current)
	 * profiles.  AppArmor rules currently have the implicit assumption
	 * that the task is setting the resource of a task confined with
	 * the same profile or that the task setting the resource of another
	 * task has CAP_SYS_RESOURCE.
	 */

	if (label != peer &&
	    aa_capable(label, CAP_SYS_RESOURCE, CAP_OPT_NOAUDIT) != 0)
		error = fn_for_each(label, profile,
				audit_resource(profile, resource,
					       new_rlim->rlim_max, peer,
					       "cap_sys_resource", -EACCES));
	else
		error = fn_for_each_confined(label, profile,
				profile_setrlimit(profile, resource, new_rlim));
	aa_put_label(peer);

	return error;
}