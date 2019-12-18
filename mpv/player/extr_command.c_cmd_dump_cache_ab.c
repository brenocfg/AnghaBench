#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_cmd_ctx {TYPE_3__* args; struct MPContext* mpctx; } ;
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ab_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  run_dump_cmd (struct mp_cmd_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_dump_cache_ab(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    run_dump_cmd(cmd, mpctx->opts->ab_loop[0], mpctx->opts->ab_loop[1],
                 cmd->args[0].v.s);
}