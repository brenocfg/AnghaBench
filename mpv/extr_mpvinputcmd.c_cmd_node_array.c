#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct mp_cmd {int /*<<< orphan*/  nargs; } ;
struct TYPE_13__ {int num; TYPE_6__* values; } ;
typedef  TYPE_3__ mpv_node_list ;
struct TYPE_11__ {TYPE_3__* list; } ;
struct TYPE_14__ {scalar_t__ format; TYPE_1__ u; } ;
typedef  TYPE_4__ mpv_node ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ bstr ;
struct TYPE_12__ {int /*<<< orphan*/  string; } ;
struct TYPE_16__ {scalar_t__ format; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_NODE_ARRAY ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  apply_flag (struct mp_cmd*,TYPE_5__) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__ bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_cmd (struct mp_log*,struct mp_cmd*,TYPE_5__) ; 
 int /*<<< orphan*/  set_node_arg (struct mp_log*,struct mp_cmd*,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static bool cmd_node_array(struct mp_log *log, struct mp_cmd *cmd, mpv_node *node)
{
    assert(node->format == MPV_FORMAT_NODE_ARRAY);
    mpv_node_list *args = node->u.list;
    int cur = 0;

    while (cur < args->num) {
        if (args->values[cur].format != MPV_FORMAT_STRING)
            break;
        if (!apply_flag(cmd, bstr0(args->values[cur].u.string)))
            break;
        cur++;
    }

    bstr cmd_name = {0};
    if (cur < args->num && args->values[cur].format == MPV_FORMAT_STRING)
        cmd_name = bstr0(args->values[cur++].u.string);
    if (!find_cmd(log, cmd, cmd_name))
        return false;

    int first = cur;
    for (int i = 0; i < args->num - first; i++) {
        if (!set_node_arg(log, cmd, cmd->nargs, &args->values[cur++]))
            return false;
    }

    return true;
}