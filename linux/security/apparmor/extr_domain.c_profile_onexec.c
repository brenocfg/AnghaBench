#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path_cond {int /*<<< orphan*/  uid; } ;
struct linux_binprm {char* filename; TYPE_1__* file; } ;
struct TYPE_6__ {unsigned int start; int /*<<< orphan*/  dfa; } ;
struct TYPE_5__ {int flags; } ;
struct aa_profile {TYPE_3__ file; TYPE_2__ label; int /*<<< orphan*/  disconnected; int /*<<< orphan*/  path_flags; } ;
struct aa_perms {int allow; int xindex; } ;
struct aa_label {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_DEBUG (char*) ; 
 int AA_MAY_ONEXEC ; 
 int AA_X_UNSAFE ; 
 scalar_t__ DEBUG_ON ; 
 int EACCES ; 
 int FLAG_IX_ON_NAME_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  OP_EXEC ; 
 int aa_audit_file (struct aa_profile*,struct aa_perms*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char const*,int) ; 
 unsigned int aa_dfa_null_transition (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  aa_label_printk (struct aa_label*,int /*<<< orphan*/ ) ; 
 int aa_path_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const**,char const**,int /*<<< orphan*/ ) ; 
 unsigned int aa_str_perms (int /*<<< orphan*/ ,unsigned int,char const*,struct path_cond*,struct aa_perms*) ; 
 int change_profile_perms (struct aa_profile*,struct aa_label*,int,int,unsigned int,struct aa_perms*) ; 
 int /*<<< orphan*/  dbg_printk (char*,...) ; 
 scalar_t__ profile_unconfined (struct aa_profile*) ; 

__attribute__((used)) static int profile_onexec(struct aa_profile *profile, struct aa_label *onexec,
			  bool stack, const struct linux_binprm *bprm,
			  char *buffer, struct path_cond *cond,
			  bool *secure_exec)
{
	unsigned int state = profile->file.start;
	struct aa_perms perms = {};
	const char *xname = NULL, *info = "change_profile onexec";
	int error = -EACCES;

	AA_BUG(!profile);
	AA_BUG(!onexec);
	AA_BUG(!bprm);
	AA_BUG(!buffer);

	if (profile_unconfined(profile)) {
		/* change_profile on exec already granted */
		/*
		 * NOTE: Domain transitions from unconfined are allowed
		 * even when no_new_privs is set because this aways results
		 * in a further reduction of permissions.
		 */
		return 0;
	}

	error = aa_path_name(&bprm->file->f_path, profile->path_flags, buffer,
			     &xname, &info, profile->disconnected);
	if (error) {
		if (profile_unconfined(profile) ||
		    (profile->label.flags & FLAG_IX_ON_NAME_ERROR)) {
			AA_DEBUG("name lookup ix on error");
			error = 0;
		}
		xname = bprm->filename;
		goto audit;
	}

	/* find exec permissions for name */
	state = aa_str_perms(profile->file.dfa, state, xname, cond, &perms);
	if (!(perms.allow & AA_MAY_ONEXEC)) {
		info = "no change_onexec valid for executable";
		goto audit;
	}
	/* test if this exec can be paired with change_profile onexec.
	 * onexec permission is linked to exec with a standard pairing
	 * exec\0change_profile
	 */
	state = aa_dfa_null_transition(profile->file.dfa, state);
	error = change_profile_perms(profile, onexec, stack, AA_MAY_ONEXEC,
				     state, &perms);
	if (error) {
		perms.allow &= ~AA_MAY_ONEXEC;
		goto audit;
	}

	if (!(perms.xindex & AA_X_UNSAFE)) {
		if (DEBUG_ON) {
			dbg_printk("apparmor: scrubbing environment "
				   "variables for %s label=", xname);
			aa_label_printk(onexec, GFP_ATOMIC);
			dbg_printk("\n");
		}
		*secure_exec = true;
	}

audit:
	return aa_audit_file(profile, &perms, OP_EXEC, AA_MAY_ONEXEC, xname,
			     NULL, onexec, cond->uid, info, error);
}