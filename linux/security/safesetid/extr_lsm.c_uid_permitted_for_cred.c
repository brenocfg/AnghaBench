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
struct cred {int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 scalar_t__ SIDPOL_CONSTRAINED ; 
 int /*<<< orphan*/  __kuid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setuid_policy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool uid_permitted_for_cred(const struct cred *old, kuid_t new_uid)
{
	bool permitted;

	/* If our old creds already had this UID in it, it's fine. */
	if (uid_eq(new_uid, old->uid) || uid_eq(new_uid, old->euid) ||
	    uid_eq(new_uid, old->suid))
		return true;

	/*
	 * Transitions to new UIDs require a check against the policy of the old
	 * RUID.
	 */
	permitted =
	    setuid_policy_lookup(old->uid, new_uid) != SIDPOL_CONSTRAINED;
	if (!permitted) {
		pr_warn("UID transition ((%d,%d,%d) -> %d) blocked\n",
			__kuid_val(old->uid), __kuid_val(old->euid),
			__kuid_val(old->suid), __kuid_val(new_uid));
	}
	return permitted;
}