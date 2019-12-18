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
struct priv {double pitch; } ;
struct mp_filter_command {int type; int /*<<< orphan*/  speed; int /*<<< orphan*/  arg; int /*<<< orphan*/  cmd; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
#define  MP_FILTER_COMMAND_SET_SPEED 129 
#define  MP_FILTER_COMMAND_TEXT 128 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 double strtod (int /*<<< orphan*/ ,char**) ; 
 int update_pitch (struct priv*,double) ; 
 int /*<<< orphan*/  update_speed (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool command(struct mp_filter *f, struct mp_filter_command *cmd)
{
    struct priv *p = f->priv;

    switch (cmd->type) {
    case MP_FILTER_COMMAND_TEXT: {
        char *endptr = NULL;
        double pitch = p->pitch;
        if (!strcmp(cmd->cmd, "set-pitch")) {
            pitch = strtod(cmd->arg, &endptr);
            if (*endptr)
                return false;
            return update_pitch(p, pitch);
        } else if (!strcmp(cmd->cmd, "multiply-pitch")) {
            double mult = strtod(cmd->arg, &endptr);
            if (*endptr || mult <= 0)
                return false;
            pitch *= mult;
            return update_pitch(p, pitch);
        }
        return false;
    }
    case MP_FILTER_COMMAND_SET_SPEED:
        update_speed(p, cmd->speed);
        return true;
    }

    return false;
}