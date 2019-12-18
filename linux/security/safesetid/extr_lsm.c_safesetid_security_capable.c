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
struct user_namespace {int dummy; } ;
struct cred {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 unsigned int CAP_OPT_INSETID ; 
 int CAP_SETUID ; 
 int EPERM ; 
 int /*<<< orphan*/  INVALID_UID ; 
 scalar_t__ SIDPOL_DEFAULT ; 
 int /*<<< orphan*/  __kuid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ setuid_policy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safesetid_security_capable(const struct cred *cred,
				      struct user_namespace *ns,
				      int cap,
				      unsigned int opts)
{
	/* We're only interested in CAP_SETUID. */
	if (cap != CAP_SETUID)
		return 0;

	/*
	 * If CAP_SETUID is currently used for a set*uid() syscall, we want to
	 * let it go through here; the real security check happens later, in the
	 * task_fix_setuid hook.
	 */
	if ((opts & CAP_OPT_INSETID) != 0)
		return 0;

	/*
	 * If no policy applies to this task, allow the use of CAP_SETUID for
	 * other purposes.
	 */
	if (setuid_policy_lookup(cred->uid, INVALID_UID) == SIDPOL_DEFAULT)
		return 0;

	/*
	 * Reject use of CAP_SETUID for functionality other than calling
	 * set*uid() (e.g. setting up userns uid mappings).
	 */
	pr_warn("Operation requires CAP_SETUID, which is not available to UID %u for operations besides approved set*uid transitions\n",
		__kuid_val(cred->uid));
	return -EPERM;
}