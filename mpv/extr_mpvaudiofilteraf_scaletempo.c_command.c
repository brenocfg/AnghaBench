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
struct priv {TYPE_1__* opts; } ;
struct mp_filter_command {scalar_t__ type; int /*<<< orphan*/  speed; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_2__ {int speed_opt; } ;

/* Variables and functions */
 scalar_t__ MP_FILTER_COMMAND_SET_SPEED ; 
 int SCALE_PITCH ; 
 int SCALE_TEMPO ; 
 int /*<<< orphan*/  update_speed (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool command(struct mp_filter *f, struct mp_filter_command *cmd)
{
    struct priv *s = f->priv;

    if (cmd->type == MP_FILTER_COMMAND_SET_SPEED) {
        if (s->opts->speed_opt & SCALE_TEMPO) {
            if (s->opts->speed_opt & SCALE_PITCH)
                return false;
            update_speed(s, cmd->speed);
            return true;
        } else if (s->opts->speed_opt & SCALE_PITCH) {
            update_speed(s, cmd->speed);
            return false; // do not signal OK
        }
    }

    return false;
}