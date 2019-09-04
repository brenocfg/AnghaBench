#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct mp_cmd_def {scalar_t__ vararg; struct m_option* args; scalar_t__ name; } ;
struct m_option {int flags; TYPE_1__* type; int /*<<< orphan*/  name; scalar_t__ defval; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MP_CMD_DEF_MAX_ARGS ; 
 int MP_CMD_OPT_ARG ; 
 struct mp_cmd_def* mp_cmds ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 

void mp_print_cmd_list(struct mp_log *out)
{
    for (int i = 0; mp_cmds[i].name; i++) {
        const struct mp_cmd_def *def = &mp_cmds[i];
        mp_info(out, "%-20.20s", def->name);
        for (int j = 0; j < MP_CMD_DEF_MAX_ARGS && def->args[j].type; j++) {
            const struct m_option *arg = &def->args[j];
            bool is_opt = arg->defval || (arg->flags & MP_CMD_OPT_ARG);
            mp_info(out, " %s%s=%s%s", is_opt ? "[" : "", arg->name,
                    arg->type->name, is_opt ? "]" : "");
        }
        if (def->vararg)
            mp_info(out, "..."); // essentially append to last argument
        mp_info(out, "\n");
    }
}