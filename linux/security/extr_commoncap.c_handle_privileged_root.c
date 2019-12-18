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
struct linux_binprm {int /*<<< orphan*/  filename; struct cred* cred; } ;
struct cred {int /*<<< orphan*/  cap_inheritable; int /*<<< orphan*/  cap_bset; int /*<<< orphan*/  cap_permitted; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 scalar_t__ __is_eff (int /*<<< orphan*/ ,struct cred*) ; 
 scalar_t__ __is_real (int /*<<< orphan*/ ,struct cred*) ; 
 scalar_t__ __is_suid (int /*<<< orphan*/ ,struct cred*) ; 
 int /*<<< orphan*/  cap_combine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  root_privileged () ; 
 int /*<<< orphan*/  warn_setuid_and_fcaps_mixed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_privileged_root(struct linux_binprm *bprm, bool has_fcap,
				   bool *effective, kuid_t root_uid)
{
	const struct cred *old = current_cred();
	struct cred *new = bprm->cred;

	if (!root_privileged())
		return;
	/*
	 * If the legacy file capability is set, then don't set privs
	 * for a setuid root binary run by a non-root user.  Do set it
	 * for a root user just to cause least surprise to an admin.
	 */
	if (has_fcap && __is_suid(root_uid, new)) {
		warn_setuid_and_fcaps_mixed(bprm->filename);
		return;
	}
	/*
	 * To support inheritance of root-permissions and suid-root
	 * executables under compatibility mode, we override the
	 * capability sets for the file.
	 */
	if (__is_eff(root_uid, new) || __is_real(root_uid, new)) {
		/* pP' = (cap_bset & ~0) | (pI & ~0) */
		new->cap_permitted = cap_combine(old->cap_bset,
						 old->cap_inheritable);
	}
	/*
	 * If only the real uid is 0, we do not set the effective bit.
	 */
	if (__is_eff(root_uid, new))
		*effective = true;
}