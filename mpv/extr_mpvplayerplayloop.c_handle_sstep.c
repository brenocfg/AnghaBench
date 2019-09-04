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
struct MPOpts {scalar_t__ step_sec; } ;
struct MPContext {scalar_t__ video_status; scalar_t__ max_frames; scalar_t__ step_frames; int /*<<< orphan*/  paused; scalar_t__ stop_play; int /*<<< orphan*/  restart_complete; struct MPOpts* opts; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 int /*<<< orphan*/  MPSEEK_DEFAULT ; 
 int /*<<< orphan*/  MPSEEK_RELATIVE ; 
 int /*<<< orphan*/  OSD_FFW ; 
 scalar_t__ STATUS_EOF ; 
 int /*<<< orphan*/  queue_seek (struct MPContext*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_osd_function (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pause_state (struct MPContext*,int) ; 

__attribute__((used)) static void handle_sstep(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    if (mpctx->stop_play || !mpctx->restart_complete)
        return;

    if (opts->step_sec > 0 && !mpctx->paused) {
        set_osd_function(mpctx, OSD_FFW);
        queue_seek(mpctx, MPSEEK_RELATIVE, opts->step_sec, MPSEEK_DEFAULT, 0);
    }

    if (mpctx->video_status >= STATUS_EOF) {
        if (mpctx->max_frames >= 0 && !mpctx->stop_play)
            mpctx->stop_play = AT_END_OF_FILE; // force EOF even if audio left
        if (mpctx->step_frames > 0 && !mpctx->paused)
            set_pause_state(mpctx, true);
    }
}