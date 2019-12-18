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
struct aa_task_ctx {scalar_t__ token; int /*<<< orphan*/  previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int EACCES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  aa_clear_task_ctx_trans (struct aa_task_ctx*) ; 
 int /*<<< orphan*/  aa_get_newest_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 int /*<<< orphan*/  cred_label (struct cred*) ; 
 int /*<<< orphan*/  current ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  set_cred_label (struct cred*,int /*<<< orphan*/ ) ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 

int aa_restore_previous_label(u64 token)
{
	struct aa_task_ctx *ctx = task_ctx(current);
	struct cred *new;

	if (ctx->token != token)
		return -EACCES;
	/* ignore restores when there is no saved label */
	if (!ctx->previous)
		return 0;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	aa_put_label(cred_label(new));
	set_cred_label(new, aa_get_newest_label(ctx->previous));
	AA_BUG(!cred_label(new));
	/* clear exec && prev information when restoring to previous context */
	aa_clear_task_ctx_trans(ctx);

	commit_creds(new);

	return 0;
}