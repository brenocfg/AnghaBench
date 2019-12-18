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
struct cred {int dummy; } ;
struct aa_task_ctx {struct aa_label* nnp; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  aa_clear_task_ctx_trans (struct aa_task_ctx*) ; 
 struct aa_label* aa_current_raw_label () ; 
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 struct aa_label* aa_get_newest_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 struct aa_label* cred_label (struct cred*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ current_cred () ; 
 scalar_t__ current_real_cred () ; 
 scalar_t__ label_is_stale (struct aa_label*) ; 
 scalar_t__ labels_ns (struct aa_label*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  set_cred_label (struct cred*,struct aa_label*) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unconfined (struct aa_label*) ; 

int aa_replace_current_label(struct aa_label *label)
{
	struct aa_label *old = aa_current_raw_label();
	struct aa_task_ctx *ctx = task_ctx(current);
	struct cred *new;

	AA_BUG(!label);

	if (old == label)
		return 0;

	if (current_cred() != current_real_cred())
		return -EBUSY;

	new  = prepare_creds();
	if (!new)
		return -ENOMEM;

	if (ctx->nnp && label_is_stale(ctx->nnp)) {
		struct aa_label *tmp = ctx->nnp;

		ctx->nnp = aa_get_newest_label(tmp);
		aa_put_label(tmp);
	}
	if (unconfined(label) || (labels_ns(old) != labels_ns(label)))
		/*
		 * if switching to unconfined or a different label namespace
		 * clear out context state
		 */
		aa_clear_task_ctx_trans(task_ctx(current));

	/*
	 * be careful switching cred label, when racing replacement it
	 * is possible that the cred labels's->proxy->label is the reference
	 * keeping @label valid, so make sure to get its reference before
	 * dropping the reference on the cred's label
	 */
	aa_get_label(label);
	aa_put_label(cred_label(new));
	set_cred_label(new, label);

	commit_creds(new);
	return 0;
}