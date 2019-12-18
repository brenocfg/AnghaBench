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
typedef  scalar_t__ u64 ;
struct cred {int dummy; } ;
struct aa_task_ctx {scalar_t__ token; int /*<<< orphan*/ * onexec; int /*<<< orphan*/ * previous; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  aa_get_newest_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 int /*<<< orphan*/ * cred_label (struct cred*) ; 
 int /*<<< orphan*/  current ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  set_cred_label (struct cred*,int /*<<< orphan*/ ) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 

int aa_set_current_hat(struct aa_label *label, u64 token)
{
	struct aa_task_ctx *ctx = task_ctx(current);
	struct cred *new;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;
	AA_BUG(!label);

	if (!ctx->previous) {
		/* transfer refcount */
		ctx->previous = cred_label(new);
		ctx->token = token;
	} else if (ctx->token == token) {
		aa_put_label(cred_label(new));
	} else {
		/* previous_profile && ctx->token != token */
		abort_creds(new);
		return -EACCES;
	}

	set_cred_label(new, aa_get_newest_label(label));
	/* clear exec on switching context */
	aa_put_label(ctx->onexec);
	ctx->onexec = NULL;

	commit_creds(new);
	return 0;
}