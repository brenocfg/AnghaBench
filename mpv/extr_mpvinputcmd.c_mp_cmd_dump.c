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
struct mp_cmd {int nargs; TYPE_1__* args; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 char* m_option_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_msg (struct mp_log*,int,char*,...) ; 
 int /*<<< orphan*/  mp_msg_test (struct mp_log*,int) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

void mp_cmd_dump(struct mp_log *log, int msgl, char *header, struct mp_cmd *cmd)
{
    if (!mp_msg_test(log, msgl))
        return;
    if (header)
        mp_msg(log, msgl, "%s ", header);
    if (!cmd) {
        mp_msg(log, msgl, "(NULL)\n");
        return;
    }
    mp_msg(log, msgl, "%s, flags=%d, args=[", cmd->name, cmd->flags);
    for (int n = 0; n < cmd->nargs; n++) {
        char *s = m_option_print(cmd->args[n].type, &cmd->args[n].v);
        if (n)
            mp_msg(log, msgl, ", ");
        mp_msg(log, msgl, "%s", s ? s : "(NULL)");
        talloc_free(s);
    }
    mp_msg(log, msgl, "]\n");
}