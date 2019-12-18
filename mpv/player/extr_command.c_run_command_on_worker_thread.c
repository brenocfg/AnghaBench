#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_cmd_ctx {TYPE_2__* cmd; struct MPContext* mpctx; } ;
struct MPContext {int outstanding_async; } ;
struct TYPE_4__ {TYPE_1__* def; } ;
struct TYPE_3__ {int exec_async; int /*<<< orphan*/  (* handler ) (struct mp_cmd_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mp_cmd_ctx_complete (struct mp_cmd_ctx*) ; 
 int /*<<< orphan*/  mp_core_lock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_unlock (struct MPContext*) ; 
 scalar_t__ mp_is_shutting_down (struct MPContext*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  stub1 (struct mp_cmd_ctx*) ; 

__attribute__((used)) static void run_command_on_worker_thread(void *p)
{
    struct mp_cmd_ctx *ctx = p;
    struct MPContext *mpctx = ctx->mpctx;

    mp_core_lock(mpctx);

    bool exec_async = ctx->cmd->def->exec_async;
    ctx->cmd->def->handler(ctx);
    if (!exec_async)
        mp_cmd_ctx_complete(ctx);

    mpctx->outstanding_async -= 1;
    if (!mpctx->outstanding_async && mp_is_shutting_down(mpctx))
        mp_wakeup_core(mpctx);

    mp_core_unlock(mpctx);
}