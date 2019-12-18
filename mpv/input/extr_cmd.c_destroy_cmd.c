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
struct mp_cmd {int nargs; TYPE_1__* args; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_option_free (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_cmd(void *ptr)
{
    struct mp_cmd *cmd = ptr;
    for (int n = 0; n < cmd->nargs; n++) {
        if (cmd->args[n].type)
            m_option_free(cmd->args[n].type, &cmd->args[n].v);
    }
}