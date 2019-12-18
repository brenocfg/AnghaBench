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
struct mp_cmd_ctx {int success; TYPE_1__* cmd; struct MPContext* mpctx; } ;
struct MPContext {int step_frames; int /*<<< orphan*/  playback_initialized; } ;
struct TYPE_2__ {scalar_t__ repeated; scalar_t__ is_up; scalar_t__ is_up_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_step_frame (struct MPContext*,int) ; 
 int /*<<< orphan*/  set_pause_state (struct MPContext*,int) ; 

__attribute__((used)) static void cmd_frame_step(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    if (!mpctx->playback_initialized) {
        cmd->success = false;
        return;
    }

    if (cmd->cmd->is_up_down) {
        if (cmd->cmd->is_up) {
            if (mpctx->step_frames < 1)
                set_pause_state(mpctx, true);
        } else {
            if (cmd->cmd->repeated) {
                set_pause_state(mpctx, false);
            } else {
                add_step_frame(mpctx, 1);
            }
        }
    } else {
        add_step_frame(mpctx, 1);
    }
}