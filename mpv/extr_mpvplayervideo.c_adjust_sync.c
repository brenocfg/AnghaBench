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
struct MPOpts {double audio_delay; double default_max_pts_correction; } ;
struct MPContext {scalar_t__ audio_status; double delay; scalar_t__ total_avsync_change; scalar_t__ display_sync_active; struct MPOpts* opts; } ;

/* Variables and functions */
 scalar_t__ STATUS_PLAYING ; 
 double fabs (double) ; 
 double written_audio_pts (struct MPContext*) ; 

__attribute__((used)) static void adjust_sync(struct MPContext *mpctx, double v_pts, double frame_time)
{
    struct MPOpts *opts = mpctx->opts;

    if (mpctx->audio_status != STATUS_PLAYING)
        return;

    double a_pts = written_audio_pts(mpctx) + opts->audio_delay - mpctx->delay;
    double av_delay = a_pts - v_pts;

    double change = av_delay * 0.1;
    double factor = fabs(av_delay) < 0.3 ? 0.1 : 0.4;
    double max_change = opts->default_max_pts_correction >= 0 ?
                        opts->default_max_pts_correction : frame_time * factor;
    if (change < -max_change)
        change = -max_change;
    else if (change > max_change)
        change = max_change;
    mpctx->delay += change;
    mpctx->total_avsync_change += change;

    if (mpctx->display_sync_active)
        mpctx->total_avsync_change = 0;
}