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
struct mp_cmd_def {struct m_option* args; } ;
struct m_option {scalar_t__ type; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 int MP_CMD_DEF_MAX_ARGS ; 
 scalar_t__ is_vararg (struct mp_cmd_def const*,int) ; 

__attribute__((used)) static const struct m_option *get_arg_type(const struct mp_cmd_def *cmd, int i)
{
    const struct m_option *opt = NULL;
    if (is_vararg(cmd, i)) {
        // The last arg in a vararg command sets all vararg types.
        for (int n = MPMIN(i, MP_CMD_DEF_MAX_ARGS - 1); n >= 0; n--) {
            if (cmd->args[n].type) {
                opt = &cmd->args[n];
                break;
            }
        }
    } else if (i < MP_CMD_DEF_MAX_ARGS) {
        opt = &cmd->args[i];
    }
    return opt && opt->type ? opt : NULL;
}