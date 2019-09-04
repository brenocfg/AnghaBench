#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vo_chain {TYPE_3__* track; TYPE_1__* filter; } ;
struct MPOpts {int frame_dropping; } ;
struct MPContext {scalar_t__ video_status; scalar_t__ audio_status; double last_av_difference; int /*<<< orphan*/  ao; int /*<<< orphan*/  paused; struct MPOpts* opts; } ;
struct TYPE_6__ {TYPE_2__* dec; } ;
struct TYPE_5__ {int /*<<< orphan*/  attempt_framedrops; } ;
struct TYPE_4__ {float container_fps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCLAMP (double,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  ao_untimed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_framedrop(struct MPContext *mpctx, struct vo_chain *vo_c)
{
    struct MPOpts *opts = mpctx->opts;
    // check for frame-drop:
    if (mpctx->video_status == STATUS_PLAYING && !mpctx->paused &&
        mpctx->audio_status == STATUS_PLAYING && !ao_untimed(mpctx->ao) &&
        vo_c->track && vo_c->track->dec && (opts->frame_dropping & 2))
    {
        float fps = vo_c->filter->container_fps;
        // it's a crappy heuristic; avoid getting upset by incorrect fps
        if (fps <= 20 || fps >= 500)
            return;
        double frame_time =  1.0 / fps;
        // try to drop as many frames as we appear to be behind
        vo_c->track->dec->attempt_framedrops =
            MPCLAMP((mpctx->last_av_difference - 0.010) / frame_time, 0, 100);
    }
}