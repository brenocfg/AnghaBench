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
struct tomoyo_domain_info {int /*<<< orphan*/  users; } ;
struct linux_binprm {TYPE_1__* cred; int /*<<< orphan*/  filename; scalar_t__ called_set_creds; } ;
struct TYPE_2__ {int /*<<< orphan*/ * security; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_load_policy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_policy_loaded ; 

__attribute__((used)) static int tomoyo_bprm_set_creds(struct linux_binprm *bprm)
{
	/*
	 * Do only if this function is called for the first time of an execve
	 * operation.
	 */
	if (bprm->called_set_creds)
		return 0;
#ifndef CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER
	/*
	 * Load policy if /sbin/tomoyo-init exists and /sbin/init is requested
	 * for the first time.
	 */
	if (!tomoyo_policy_loaded)
		tomoyo_load_policy(bprm->filename);
#endif
	/*
	 * Release reference to "struct tomoyo_domain_info" stored inside
	 * "bprm->cred->security". New reference to "struct tomoyo_domain_info"
	 * stored inside "bprm->cred->security" will be acquired later inside
	 * tomoyo_find_next_domain().
	 */
	atomic_dec(&((struct tomoyo_domain_info *)
		     bprm->cred->security)->users);
	/*
	 * Tell tomoyo_bprm_check_security() is called for the first time of an
	 * execve operation.
	 */
	bprm->cred->security = NULL;
	return 0;
}