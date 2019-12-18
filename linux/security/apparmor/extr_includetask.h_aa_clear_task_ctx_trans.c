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
struct aa_task_ctx {scalar_t__ token; int /*<<< orphan*/ * onexec; int /*<<< orphan*/ * previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void aa_clear_task_ctx_trans(struct aa_task_ctx *ctx)
{
	AA_BUG(!ctx);

	aa_put_label(ctx->previous);
	aa_put_label(ctx->onexec);
	ctx->previous = NULL;
	ctx->onexec = NULL;
	ctx->token = 0;
}