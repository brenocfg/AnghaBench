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
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;
struct priv {double audio_speed; int resampling_forced; TYPE_1__ sub; } ;
struct mp_filter_command {scalar_t__ type; double speed; int is_active; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 scalar_t__ MP_FILTER_COMMAND_IS_ACTIVE ; 
 scalar_t__ MP_FILTER_COMMAND_SET_SPEED_RESAMPLE ; 

__attribute__((used)) static bool command(struct mp_filter *f, struct mp_filter_command *cmd)
{
    struct priv *p = f->priv;

    if (cmd->type == MP_FILTER_COMMAND_SET_SPEED_RESAMPLE) {
        p->audio_speed = cmd->speed;
        // If we needed resampling once, keep forcing resampling, as it might be
        // quickly changing between 1.0 and other values for A/V compensation.
        if (p->audio_speed != 1.0)
            p->resampling_forced = true;
        return true;
    }

    if (cmd->type == MP_FILTER_COMMAND_IS_ACTIVE) {
        cmd->is_active = !!p->sub.filter;
        return true;
    }

    return false;
}