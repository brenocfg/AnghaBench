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
struct MPOpts {double audio_delay; } ;
struct MPContext {double last_av_difference; scalar_t__ audio_status; scalar_t__ video_status; double video_pts; int drop_message_shown; TYPE_1__* vo_chain; struct MPOpts* opts; } ;
struct TYPE_2__ {scalar_t__ is_sparse; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  av_desync_help_text ; 
 double fabs (double) ; 
 double playing_audio_pts (struct MPContext*) ; 

__attribute__((used)) static void update_av_diff(struct MPContext *mpctx, double offset)
{
    struct MPOpts *opts = mpctx->opts;

    mpctx->last_av_difference = 0;

    if (mpctx->audio_status != STATUS_PLAYING ||
        mpctx->video_status != STATUS_PLAYING)
        return;

    if (mpctx->vo_chain && mpctx->vo_chain->is_sparse)
        return;

    double a_pos = playing_audio_pts(mpctx);
    if (a_pos != MP_NOPTS_VALUE && mpctx->video_pts != MP_NOPTS_VALUE) {
        mpctx->last_av_difference = a_pos - mpctx->video_pts
                                  + opts->audio_delay + offset;
    }

    if (fabs(mpctx->last_av_difference) > 0.5 && !mpctx->drop_message_shown) {
        MP_WARN(mpctx, "%s", av_desync_help_text);
        mpctx->drop_message_shown = true;
    }
}