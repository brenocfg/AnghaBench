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
struct mp_cmd_ctx {int /*<<< orphan*/  success; TYPE_3__* args; TYPE_1__* cmd; int /*<<< orphan*/  priv; struct MPContext* mpctx; } ;
struct m_property_switch_arg {double inc; int wrap; } ;
struct MPContext {int dummy; } ;
struct TYPE_5__ {char* s; double d; } ;
struct TYPE_6__ {TYPE_2__ v; } ;
struct TYPE_4__ {int scale_units; double scale; int /*<<< orphan*/  original; scalar_t__ repeated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROPERTY_SWITCH ; 
 int /*<<< orphan*/  change_property_cmd (struct mp_cmd_ctx*,char*,int /*<<< orphan*/ ,struct m_property_switch_arg*) ; 
 int /*<<< orphan*/  check_property_autorepeat (char*,struct MPContext*) ; 
 scalar_t__ check_property_scalable (char*,struct MPContext*) ; 

__attribute__((used)) static void cmd_add_cycle(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;
    bool is_cycle = !!cmd->priv;

    char *property = cmd->args[0].v.s;
    if (cmd->cmd->repeated && !check_property_autorepeat(property, mpctx)) {
        MP_VERBOSE(mpctx, "Dropping command '%.*s' from auto-repeated key.\n",
                   BSTR_P(cmd->cmd->original));
        return;
    }

    double scale = 1;
    int scale_units = cmd->cmd->scale_units;
    if (check_property_scalable(property, mpctx)) {
        scale = cmd->cmd->scale;
        scale_units = 1;
    }

    for (int i = 0; i < scale_units; i++) {
        struct m_property_switch_arg s = {
            .inc = cmd->args[1].v.d * scale,
            .wrap = is_cycle,
        };
        change_property_cmd(cmd, property, M_PROPERTY_SWITCH, &s);
        if (!cmd->success)
            return;
    }
}