#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct mp_cmd_arg {int /*<<< orphan*/  v; struct m_option const* type; } ;
struct mp_cmd {int nargs; int flags; TYPE_1__* def; struct mp_cmd_arg* args; int /*<<< orphan*/  name; } ;
struct m_option {int flags; scalar_t__ defval; } ;
struct TYPE_4__ {scalar_t__ default_async; } ;

/* Variables and functions */
 int MP_ASYNC_CMD ; 
 int MP_CMD_DEF_MAX_ARGS ; 
 int MP_CMD_OPT_ARG ; 
 int MP_SYNC_CMD ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_cmd*,struct mp_cmd_arg*,int,struct mp_cmd_arg) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_arg_name (TYPE_1__*,int) ; 
 struct m_option* get_arg_type (TYPE_1__*,int) ; 
 scalar_t__ is_vararg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  m_option_copy (struct m_option const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool finish_cmd(struct mp_log *log, struct mp_cmd *cmd)
{
    for (int i = 0; i < MP_CMD_DEF_MAX_ARGS; i++) {
        // (type==NULL is used for yet unset arguments)
        if (i < cmd->nargs && cmd->args[i].type)
            continue;
        const struct m_option *opt = get_arg_type(cmd->def, i);
        if (i >= cmd->nargs && (!opt || is_vararg(cmd->def, i)))
            break;
        if (!opt->defval && !(opt->flags & MP_CMD_OPT_ARG)) {
            mp_err(log, "Command %s: required argument %s not set.\n",
                   cmd->name, get_arg_name(cmd->def, i));
            return false;
        }
        struct mp_cmd_arg arg = {.type = opt};
        if (opt->defval)
            m_option_copy(opt, &arg.v, opt->defval);
        assert(i <= cmd->nargs);
        if (i == cmd->nargs) {
            MP_TARRAY_APPEND(cmd, cmd->args, cmd->nargs, arg);
        } else {
            cmd->args[i] = arg;
        }
    }

    if (!(cmd->flags & (MP_ASYNC_CMD | MP_SYNC_CMD)))
        cmd->flags |= cmd->def->default_async ? MP_ASYNC_CMD : MP_SYNC_CMD;

    return true;
}