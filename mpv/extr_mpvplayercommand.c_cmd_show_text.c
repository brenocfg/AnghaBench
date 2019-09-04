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
struct TYPE_5__ {int i; int /*<<< orphan*/  s; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_4__ {int osd_duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_osd_msg (struct MPContext*,int,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_show_text(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    int osd_duration = mpctx->opts->osd_duration;

    // if no argument supplied use default osd_duration, else <arg> ms.
    set_osd_msg(mpctx, cmd->args[2].v.i,
                (cmd->args[1].v.i < 0 ? osd_duration : cmd->args[1].v.i),
                "%s", cmd->args[0].v.s);
}