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
struct path_cond {int dummy; } ;
struct linux_binprm {int /*<<< orphan*/  filename; } ;
struct aa_profile {int /*<<< orphan*/  label; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_ONEXEC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct aa_label* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  OP_CHANGE_ONEXEC ; 
 int /*<<< orphan*/  aa_audit_file (struct aa_profile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_get_newest_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_label_merge (int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ) ; 
 int fn_for_each_in_ns (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 struct aa_label* fn_label_build_in_ns (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nullperms ; 
 int /*<<< orphan*/  profile_onexec (struct aa_profile*,struct aa_label*,int,struct linux_binprm const*,char*,struct path_cond*,int*) ; 
 int /*<<< orphan*/  profile_transition (struct aa_profile*,struct linux_binprm const*,char*,struct path_cond*,int*) ; 

__attribute__((used)) static struct aa_label *handle_onexec(struct aa_label *label,
				      struct aa_label *onexec, bool stack,
				      const struct linux_binprm *bprm,
				      char *buffer, struct path_cond *cond,
				      bool *unsafe)
{
	struct aa_profile *profile;
	struct aa_label *new;
	int error;

	AA_BUG(!label);
	AA_BUG(!onexec);
	AA_BUG(!bprm);
	AA_BUG(!buffer);

	if (!stack) {
		error = fn_for_each_in_ns(label, profile,
				profile_onexec(profile, onexec, stack,
					       bprm, buffer, cond, unsafe));
		if (error)
			return ERR_PTR(error);
		new = fn_label_build_in_ns(label, profile, GFP_ATOMIC,
				aa_get_newest_label(onexec),
				profile_transition(profile, bprm, buffer,
						   cond, unsafe));

	} else {
		/* TODO: determine how much we want to loosen this */
		error = fn_for_each_in_ns(label, profile,
				profile_onexec(profile, onexec, stack, bprm,
					       buffer, cond, unsafe));
		if (error)
			return ERR_PTR(error);
		new = fn_label_build_in_ns(label, profile, GFP_ATOMIC,
				aa_label_merge(&profile->label, onexec,
					       GFP_ATOMIC),
				profile_transition(profile, bprm, buffer,
						   cond, unsafe));
	}

	if (new)
		return new;

	/* TODO: get rid of GLOBAL_ROOT_UID */
	error = fn_for_each_in_ns(label, profile,
			aa_audit_file(profile, &nullperms, OP_CHANGE_ONEXEC,
				      AA_MAY_ONEXEC, bprm->filename, NULL,
				      onexec, GLOBAL_ROOT_UID,
				      "failed to build target label", -ENOMEM));
	return ERR_PTR(error);
}