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
struct priv {int /*<<< orphan*/  cmd_speed; } ;
struct mp_filter_command {scalar_t__ type; int /*<<< orphan*/  speed; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 scalar_t__ MP_FILTER_COMMAND_SET_SPEED_RESAMPLE ; 

__attribute__((used)) static bool command(struct mp_filter *f, struct mp_filter_command *cmd)
{
    struct priv *p = f->priv;

    if (cmd->type == MP_FILTER_COMMAND_SET_SPEED_RESAMPLE) {
        p->cmd_speed = cmd->speed;
        return true;
    }

    return false;
}