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
struct aa_task_ctx {int token; struct aa_label* onexec; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  current ; 
 struct aa_task_ctx* task_ctx (int /*<<< orphan*/ ) ; 

int aa_set_current_onexec(struct aa_label *label, bool stack)
{
	struct aa_task_ctx *ctx = task_ctx(current);

	aa_get_label(label);
	aa_put_label(ctx->onexec);
	ctx->onexec = label;
	ctx->token = stack;

	return 0;
}