#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_cmd_ctx {int success; int /*<<< orphan*/  on_osd; scalar_t__ msg_osd; TYPE_2__* args; struct MPContext* mpctx; } ;
struct m_option_type {struct m_option_action* actions; } ;
struct m_option_action {scalar_t__ name; } ;
struct m_config_option {TYPE_4__* opt; } ;
struct MPContext {int /*<<< orphan*/  mconfig; TYPE_3__* opts; } ;
struct TYPE_8__ {struct m_option_type* type; } ;
struct TYPE_7__ {int osd_duration; } ;
struct TYPE_5__ {char* s; } ;
struct TYPE_6__ {TYPE_1__ v; } ;

/* Variables and functions */
 int OSD_LEVEL_INVISIBLE ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 struct m_config_option* m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int m_config_set_option_cli (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mp_tprintf (int,char*,char*,char*) ; 
 int /*<<< orphan*/  set_osd_msg (struct MPContext*,int,int,char*,char*) ; 
 int /*<<< orphan*/  show_property_osd (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void cmd_change_list(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    char *name = cmd->args[0].v.s;
    char *op = cmd->args[1].v.s;
    char *value = cmd->args[2].v.s;
    int osd_duration = mpctx->opts->osd_duration;
    int osdl = cmd->msg_osd ? 1 : OSD_LEVEL_INVISIBLE;

    struct m_config_option *co = m_config_get_co(mpctx->mconfig, bstr0(name));
    if (!co) {
        set_osd_msg(mpctx, osdl, osd_duration, "Unknown option: '%s'", name);
        cmd->success = false;
        return;
    }

    const struct m_option_type *type = co->opt->type;
    bool found = false;
    for (int i = 0; type->actions && type->actions[i].name; i++) {
        const struct m_option_action *action = &type->actions[i];
        if (strcmp(action->name, op) == 0)
            found = true;
    }
    if (!found) {
        set_osd_msg(mpctx, osdl, osd_duration, "Unknown action: '%s'", op);
        cmd->success = false;
        return;
    }

    char *optname = mp_tprintf(80, "%s-%s", name, op); // the dirty truth
    int r = m_config_set_option_cli(mpctx->mconfig, bstr0(optname),
                                    bstr0(value), 0);
    if (r < 0) {
        set_osd_msg(mpctx, osdl, osd_duration,
                    "Failed setting option: '%s'", name);
        cmd->success = false;
        return;
    }

    show_property_osd(mpctx, name, cmd->on_osd);
}