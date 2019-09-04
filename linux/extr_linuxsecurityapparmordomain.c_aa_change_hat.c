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
typedef  int /*<<< orphan*/  u64 ;
struct cred {int dummy; } ;
struct aa_task_ctx {scalar_t__ nnp; int /*<<< orphan*/  previous; } ;
struct aa_profile {int dummy; } ;
struct aa_perms {int /*<<< orphan*/  kill; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int AA_CHANGE_TEST ; 
 int /*<<< orphan*/  AA_DEBUG (char*) ; 
 int /*<<< orphan*/  AA_MAY_CHANGEHAT ; 
 int EACCES ; 
 int EPERM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  OP_CHANGE_HAT ; 
 int PTR_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  aa_audit_file (struct aa_profile*,struct aa_perms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ aa_get_label (struct aa_label*) ; 
 struct aa_label* aa_get_newest_cred_label (struct cred const*) ; 
 struct aa_label* aa_get_newest_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_label_is_subset (struct aa_label*,scalar_t__) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int aa_restore_previous_label (int /*<<< orphan*/ ) ; 
 int aa_set_current_hat (struct aa_label*,int /*<<< orphan*/ ) ; 
 struct aa_label* change_hat (struct aa_label*,char const**,int,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fn_for_each_in_ns (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 struct cred* get_current_cred () ; 
 int may_change_ptraced_domain (struct aa_label*,char const**) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ task_no_new_privs (int /*<<< orphan*/ ) ; 
 scalar_t__ unconfined (struct aa_label*) ; 

int aa_change_hat(const char *hats[], int count, u64 token, int flags)
{
	const struct cred *cred;
	struct aa_task_ctx *ctx = task_ctx(current);
	struct aa_label *label, *previous, *new = NULL, *target = NULL;
	struct aa_profile *profile;
	struct aa_perms perms = {};
	const char *info = NULL;
	int error = 0;

	/* released below */
	cred = get_current_cred();
	label = aa_get_newest_cred_label(cred);
	previous = aa_get_newest_label(ctx->previous);

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to do that yet.
	 *
	 * Testing for unconfined must be done before the subset test
	 */
	if (task_no_new_privs(current) && !unconfined(label) && !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	if (unconfined(label)) {
		info = "unconfined can not change_hat";
		error = -EPERM;
		goto fail;
	}

	if (count) {
		new = change_hat(label, hats, count, flags);
		AA_BUG(!new);
		if (IS_ERR(new)) {
			error = PTR_ERR(new);
			new = NULL;
			/* already audited */
			goto out;
		}

		error = may_change_ptraced_domain(new, &info);
		if (error)
			goto fail;

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

		if (flags & AA_CHANGE_TEST)
			goto out;

		target = new;
		error = aa_set_current_hat(new, token);
		if (error == -EACCES)
			/* kill task in case of brute force attacks */
			goto kill;
	} else if (previous && !(flags & AA_CHANGE_TEST)) {
		/*
		 * no new privs prevents domain transitions that would
		 * reduce restrictions.
		 */
		if (task_no_new_privs(current) && !unconfined(label) &&
		    !aa_label_is_subset(previous, ctx->nnp)) {
			/* not an apparmor denial per se, so don't log it */
			AA_DEBUG("no_new_privs - change_hat denied");
			error = -EPERM;
			goto out;
		}

		/* Return to saved label.  Kill task if restore fails
		 * to avoid brute force attacks
		 */
		target = previous;
		error = aa_restore_previous_label(token);
		if (error) {
			if (error == -EACCES)
				goto kill;
			goto fail;
		}
	} /* else ignore @flags && restores when there is no saved profile */

out:
	aa_put_label(new);
	aa_put_label(previous);
	aa_put_label(label);
	put_cred(cred);

	return error;

kill:
	info = "failed token match";
	perms.kill = AA_MAY_CHANGEHAT;

fail:
	fn_for_each_in_ns(label, profile,
		aa_audit_file(profile, &perms, OP_CHANGE_HAT,
			      AA_MAY_CHANGEHAT, NULL, NULL, target,
			      GLOBAL_ROOT_UID, info, error));

	goto out;
}