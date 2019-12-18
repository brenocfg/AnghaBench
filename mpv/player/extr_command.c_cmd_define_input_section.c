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
struct mp_cmd_ctx {TYPE_1__* cmd; TYPE_3__* args; struct MPContext* mpctx; } ;
struct MPContext {int /*<<< orphan*/  input; } ;
struct TYPE_5__ {int /*<<< orphan*/  i; int /*<<< orphan*/  s; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_4__ {int /*<<< orphan*/  sender; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_input_define_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_define_input_section(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    mp_input_define_section(mpctx->input, cmd->args[0].v.s, "<api>",
                            cmd->args[1].v.s, !cmd->args[2].v.i,
                            cmd->cmd->sender);
}