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
struct mp_cmd {int repeated; } ;
struct input_opts {int ar_rate; int ar_delay; } ;
struct input_ctx {int last_key_down; int ar_state; scalar_t__ last_ar; scalar_t__ last_key_down_time; int /*<<< orphan*/  current_down_cmd; struct input_opts* opts; } ;
typedef  struct mp_cmd mp_cmd_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int MP_NO_REPEAT_KEY ; 
 struct mp_cmd* mp_cmd_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_input_is_repeatable_cmd (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_time_us () ; 

__attribute__((used)) static mp_cmd_t *check_autorepeat(struct input_ctx *ictx)
{
    struct input_opts *opts = ictx->opts;

    // No input : autorepeat ?
    if (opts->ar_rate <= 0 || !ictx->current_down_cmd || !ictx->last_key_down ||
        (ictx->last_key_down & MP_NO_REPEAT_KEY) ||
        !mp_input_is_repeatable_cmd(ictx->current_down_cmd))
        ictx->ar_state = -1; // disable

    if (ictx->ar_state >= 0) {
        int64_t t = mp_time_us();
        if (ictx->last_ar + 2000000 < t)
            ictx->last_ar = t;
        // First time : wait delay
        if (ictx->ar_state == 0
            && (t - ictx->last_key_down_time) >= opts->ar_delay * 1000)
        {
            ictx->ar_state = 1;
            ictx->last_ar = ictx->last_key_down_time + opts->ar_delay * 1000;
            // Then send rate / sec event
        } else if (ictx->ar_state == 1
                   && (t - ictx->last_ar) >= 1000000 / opts->ar_rate) {
            ictx->last_ar += 1000000 / opts->ar_rate;
        } else {
            return NULL;
        }
        struct mp_cmd *ret = mp_cmd_clone(ictx->current_down_cmd);
        ret->repeated = true;
        return ret;
    }
    return NULL;
}