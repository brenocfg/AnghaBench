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
typedef  int /*<<< orphan*/  u32 ;
struct aa_task_ctx {scalar_t__ nnp; } ;
struct aa_label {int dummy; } ;
struct aa_profile {struct aa_label label; } ;
struct aa_perms {scalar_t__ allow; } ;

/* Variables and functions */
 int AA_CHANGE_ONEXEC ; 
 int AA_CHANGE_STACK ; 
 int AA_CHANGE_TEST ; 
 int /*<<< orphan*/  AA_DEBUG (char*) ; 
 int /*<<< orphan*/  AA_MAY_CHANGE_PROFILE ; 
 int /*<<< orphan*/  AA_MAY_ONEXEC ; 
 int /*<<< orphan*/  COMPLAIN_MODE (struct aa_profile*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct aa_label*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct aa_label*) ; 
 char* OP_CHANGE_ONEXEC ; 
 char* OP_CHANGE_PROFILE ; 
 char* OP_STACK ; 
 char* OP_STACK_ONEXEC ; 
 int PTR_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  aa_audit_file (struct aa_profile*,struct aa_perms*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char const*,int) ; 
 struct aa_label* aa_get_current_label () ; 
 scalar_t__ aa_get_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_label_is_subset (struct aa_label*,scalar_t__) ; 
 struct aa_label* aa_label_merge (struct aa_label*,struct aa_label*,int /*<<< orphan*/ ) ; 
 struct aa_label* aa_label_parse (struct aa_label*,char const*,int /*<<< orphan*/ ,int,int) ; 
 struct aa_profile* aa_new_null_profile (struct aa_profile*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int aa_replace_current_label (struct aa_label*) ; 
 int aa_set_current_onexec (struct aa_label*,int) ; 
 int /*<<< orphan*/  change_profile_perms_wrapper (char*,char const*,struct aa_profile*,struct aa_label*,int,int /*<<< orphan*/ ,struct aa_perms*) ; 
 int /*<<< orphan*/  current ; 
 int fn_for_each_in_ns (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 struct aa_label* fn_label_build_in_ns (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct aa_profile* labels_profile (struct aa_label*) ; 
 int may_change_ptraced_domain (struct aa_label*,char const**) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ task_no_new_privs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

int aa_change_profile(const char *fqname, int flags)
{
	struct aa_label *label, *new = NULL, *target = NULL;
	struct aa_profile *profile;
	struct aa_perms perms = {};
	const char *info = NULL;
	const char *auditname = fqname;		/* retain leading & if stack */
	bool stack = flags & AA_CHANGE_STACK;
	struct aa_task_ctx *ctx = task_ctx(current);
	int error = 0;
	char *op;
	u32 request;

	label = aa_get_current_label();

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to do that yet.
	 *
	 * Testing for unconfined must be done before the subset test
	 */
	if (task_no_new_privs(current) && !unconfined(label) && !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	if (!fqname || !*fqname) {
		AA_DEBUG("no profile name");
		return -EINVAL;
	}

	if (flags & AA_CHANGE_ONEXEC) {
		request = AA_MAY_ONEXEC;
		if (stack)
			op = OP_STACK_ONEXEC;
		else
			op = OP_CHANGE_ONEXEC;
	} else {
		request = AA_MAY_CHANGE_PROFILE;
		if (stack)
			op = OP_STACK;
		else
			op = OP_CHANGE_PROFILE;
	}

	label = aa_get_current_label();

	if (*fqname == '&') {
		stack = true;
		/* don't have label_parse() do stacking */
		fqname++;
	}
	target = aa_label_parse(label, fqname, GFP_KERNEL, true, false);
	if (IS_ERR(target)) {
		struct aa_profile *tprofile;

		info = "label not found";
		error = PTR_ERR(target);
		target = NULL;
		/*
		 * TODO: fixme using labels_profile is not right - do profile
		 * per complain profile
		 */
		if ((flags & AA_CHANGE_TEST) ||
		    !COMPLAIN_MODE(labels_profile(label)))
			goto audit;
		/* released below */
		tprofile = aa_new_null_profile(labels_profile(label), false,
					       fqname, GFP_KERNEL);
		if (!tprofile) {
			info = "failed null profile create";
			error = -ENOMEM;
			goto audit;
		}
		target = &tprofile->label;
		goto check;
	}

	/*
	 * self directed transitions only apply to current policy ns
	 * TODO: currently requiring perms for stacking and straight change
	 *       stacking doesn't strictly need this. Determine how much
	 *       we want to loosen this restriction for stacking
	 *
	 * if (!stack) {
	 */
	error = fn_for_each_in_ns(label, profile,
			change_profile_perms_wrapper(op, auditname,
						     profile, target, stack,
						     request, &perms));
	if (error)
		/* auditing done in change_profile_perms_wrapper */
		goto out;

	/* } */

check:
	/* check if tracing task is allowed to trace target domain */
	error = may_change_ptraced_domain(target, &info);
	if (error && !fn_for_each_in_ns(label, profile,
					COMPLAIN_MODE(profile)))
		goto audit;

	/* TODO: add permission check to allow this
	 * if ((flags & AA_CHANGE_ONEXEC) && !current_is_single_threaded()) {
	 *      info = "not a single threaded task";
	 *      error = -EACCES;
	 *      goto audit;
	 * }
	 */
	if (flags & AA_CHANGE_TEST)
		goto out;

	/* stacking is always a subset, so only check the nonstack case */
	if (!stack) {
		new = fn_label_build_in_ns(label, profile, GFP_KERNEL,
					   aa_get_label(target),
					   aa_get_label(&profile->label));
		/*
		 * no new privs prevents domain transitions that would
		 * reduce restrictions.
		 */
		if (task_no_new_privs(current) && !unconfined(label) &&
		    !aa_label_is_subset(new, ctx->nnp)) {
			/* not an apparmor denial per se, so don't log it */
			AA_DEBUG("no_new_privs - change_hat denied");
			error = -EPERM;
			goto out;
		}
	}

	if (!(flags & AA_CHANGE_ONEXEC)) {
		/* only transition profiles in the current ns */
		if (stack)
			new = aa_label_merge(label, target, GFP_KERNEL);
		if (IS_ERR_OR_NULL(new)) {
			info = "failed to build target label";
			if (!new)
				error = -ENOMEM;
			else
				error = PTR_ERR(new);
			new = NULL;
			perms.allow = 0;
			goto audit;
		}
		error = aa_replace_current_label(new);
	} else {
		if (new) {
			aa_put_label(new);
			new = NULL;
		}

		/* full transition will be built in exec path */
		error = aa_set_current_onexec(target, stack);
	}

audit:
	error = fn_for_each_in_ns(label, profile,
			aa_audit_file(profile, &perms, op, request, auditname,
				      NULL, new ? new : target,
				      GLOBAL_ROOT_UID, info, error));

out:
	aa_put_label(new);
	aa_put_label(target);
	aa_put_label(label);

	return error;
}