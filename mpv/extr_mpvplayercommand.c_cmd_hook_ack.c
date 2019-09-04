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
struct mp_cmd_ctx {int success; TYPE_3__* args; TYPE_1__* cmd; struct MPContext* mpctx; } ;
struct MPContext {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  i; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_4__ {int /*<<< orphan*/  sender; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int /*<<< orphan*/  mp_hook_continue (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_hook_ack(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    if (!cmd->cmd->sender) {
        MP_ERR(mpctx, "Can be used from client API only.\n");
        cmd->success = false;
        return;
    }
    mp_hook_continue(mpctx, cmd->cmd->sender, cmd->args[0].v.i);
}