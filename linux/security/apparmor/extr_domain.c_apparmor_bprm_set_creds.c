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
struct path_cond {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct linux_binprm {int unsafe; int secureexec; int /*<<< orphan*/  file; int /*<<< orphan*/  filename; int /*<<< orphan*/  cred; int /*<<< orphan*/  per_clear; scalar_t__ called_set_creds; } ;
struct aa_task_ctx {scalar_t__ nnp; int /*<<< orphan*/  token; scalar_t__ onexec; } ;
struct aa_profile {int dummy; } ;
struct aa_label {scalar_t__ proxy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 scalar_t__ DEBUG_ON ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct aa_label*) ; 
 int LSM_UNSAFE_NO_NEW_PRIVS ; 
 int LSM_UNSAFE_PTRACE ; 
 int LSM_UNSAFE_SHARE ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  OP_EXEC ; 
 int /*<<< orphan*/  PER_CLEAR_ON_SETID ; 
 int PTR_ERR (struct aa_label*) ; 
 int /*<<< orphan*/  aa_audit_file (struct aa_profile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aa_label*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ aa_get_label (struct aa_label*) ; 
 struct aa_label* aa_get_newest_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_label_is_subset (struct aa_label*,scalar_t__) ; 
 int /*<<< orphan*/  aa_label_printk (struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 struct aa_label* cred_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dbg_printk (char*,...) ; 
 TYPE_1__* file_inode (int /*<<< orphan*/ ) ; 
 int fn_for_each (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 struct aa_label* fn_label_build (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*) ; 
 struct aa_label* handle_onexec (struct aa_label*,scalar_t__,int /*<<< orphan*/ ,struct linux_binprm*,char*,struct path_cond*,int*) ; 
 int may_change_ptraced_domain (struct aa_label*,char const**) ; 
 int /*<<< orphan*/  nullperms ; 
 int /*<<< orphan*/  profile_transition (struct aa_profile*,struct linux_binprm*,char*,struct path_cond*,int*) ; 
 int /*<<< orphan*/  put_buffers (char*) ; 
 int /*<<< orphan*/  set_cred_label (int /*<<< orphan*/ ,struct aa_label*) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

int apparmor_bprm_set_creds(struct linux_binprm *bprm)
{
	struct aa_task_ctx *ctx;
	struct aa_label *label, *new = NULL;
	struct aa_profile *profile;
	char *buffer = NULL;
	const char *info = NULL;
	int error = 0;
	bool unsafe = false;
	struct path_cond cond = {
		file_inode(bprm->file)->i_uid,
		file_inode(bprm->file)->i_mode
	};

	if (bprm->called_set_creds)
		return 0;

	ctx = task_ctx(current);
	AA_BUG(!cred_label(bprm->cred));
	AA_BUG(!ctx);

	label = aa_get_newest_label(cred_label(bprm->cred));

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to do that yet.
	 *
	 * Testing for unconfined must be done before the subset test
	 */
	if ((bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS) && !unconfined(label) &&
	    !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	/* buffer freed below, name is pointer into buffer */
	get_buffers(buffer);
	/* Test for onexec first as onexec override other x transitions. */
	if (ctx->onexec)
		new = handle_onexec(label, ctx->onexec, ctx->token,
				    bprm, buffer, &cond, &unsafe);
	else
		new = fn_label_build(label, profile, GFP_ATOMIC,
				profile_transition(profile, bprm, buffer,
						   &cond, &unsafe));

	AA_BUG(!new);
	if (IS_ERR(new)) {
		error = PTR_ERR(new);
		goto done;
	} else if (!new) {
		error = -ENOMEM;
		goto done;
	}

	/* Policy has specified a domain transitions. If no_new_privs and
	 * confined ensure the transition is to confinement that is subset
	 * of the confinement when the task entered no new privs.
	 *
	 * NOTE: Domain transitions from unconfined and to stacked
	 * subsets are allowed even when no_new_privs is set because this
	 * aways results in a further reduction of permissions.
	 */
	if ((bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS) &&
	    !unconfined(label) && !aa_label_is_subset(new, ctx->nnp)) {
		error = -EPERM;
		info = "no new privs";
		goto audit;
	}

	if (bprm->unsafe & LSM_UNSAFE_SHARE) {
		/* FIXME: currently don't mediate shared state */
		;
	}

	if (bprm->unsafe & (LSM_UNSAFE_PTRACE)) {
		/* TODO: test needs to be profile of label to new */
		error = may_change_ptraced_domain(new, &info);
		if (error)
			goto audit;
	}

	if (unsafe) {
		if (DEBUG_ON) {
			dbg_printk("scrubbing environment variables for %s "
				   "label=", bprm->filename);
			aa_label_printk(new, GFP_ATOMIC);
			dbg_printk("\n");
		}
		bprm->secureexec = 1;
	}

	if (label->proxy != new->proxy) {
		/* when transitioning clear unsafe personality bits */
		if (DEBUG_ON) {
			dbg_printk("apparmor: clearing unsafe personality "
				   "bits. %s label=", bprm->filename);
			aa_label_printk(new, GFP_ATOMIC);
			dbg_printk("\n");
		}
		bprm->per_clear |= PER_CLEAR_ON_SETID;
	}
	aa_put_label(cred_label(bprm->cred));
	/* transfer reference, released when cred is freed */
	set_cred_label(bprm->cred, new);

done:
	aa_put_label(label);
	put_buffers(buffer);

	return error;

audit:
	error = fn_for_each(label, profile,
			aa_audit_file(profile, &nullperms, OP_EXEC, MAY_EXEC,
				      bprm->filename, NULL, new,
				      file_inode(bprm->file)->i_uid, info,
				      error));
	aa_put_label(new);
	goto done;
}