#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct mp_cmd_arg {int /*<<< orphan*/  member_0; int /*<<< orphan*/  v; struct m_option const* type; } ;
struct mp_cmd {int nargs; struct mp_cmd_arg* args; int /*<<< orphan*/  name; int /*<<< orphan*/  def; } ;
struct m_option {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {scalar_t__ format; TYPE_1__ u; } ;
typedef  TYPE_2__ mpv_node ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct mp_cmd*,struct mp_cmd_arg*,int,struct mp_cmd_arg) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 char* get_arg_name (int /*<<< orphan*/ ,int) ; 
 struct m_option* get_arg_type (int /*<<< orphan*/ ,int) ; 
 int m_option_parse (struct mp_log*,struct m_option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int m_option_set_node (struct m_option const*,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  m_option_strerror (int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool set_node_arg(struct mp_log *log, struct mp_cmd *cmd, int i,
                         mpv_node *val)
{
    const char *name = get_arg_name(cmd->def, i);

    const struct m_option *opt = get_arg_type(cmd->def, i);
    if (!opt) {
        mp_err(log, "Command %s: has only %d arguments.\n", cmd->name, i);
        return false;
    }

    if (i < cmd->nargs && cmd->args[i].type) {
        mp_err(log, "Command %s: argument %s was already set.\n", cmd->name, name);
        return false;
    }

    struct mp_cmd_arg arg = {.type = opt};
    void *dst = &arg.v;
    if (val->format == MPV_FORMAT_STRING) {
        int r = m_option_parse(log, opt, bstr0(cmd->name),
                                bstr0(val->u.string), dst);
        if (r < 0) {
            mp_err(log, "Command %s: argument %s can't be parsed: %s.\n",
                   cmd->name, name, m_option_strerror(r));
            return false;
        }
    } else {
        int r = m_option_set_node(opt, dst, val);
        if (r < 0) {
            mp_err(log, "Command %s: argument %s has incompatible type.\n",
                   cmd->name, name);
            return false;
        }
    }

    // (leave unset arguments blank, to be set later or checked by finish_cmd())
    while (i >= cmd->nargs) {
        struct mp_cmd_arg t = {0};
        MP_TARRAY_APPEND(cmd, cmd->args, cmd->nargs, t);
    }

    cmd->args[i] = arg;
    return true;
}