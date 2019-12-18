#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct MPContext {double sleeptime; scalar_t__ video_status; double start_timestamp; TYPE_2__* video_out; int /*<<< orphan*/  osd; TYPE_1__* vo_chain; int /*<<< orphan*/  paused; } ;
struct TYPE_5__ {int /*<<< orphan*/  config_ok; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_coverart; } ;

/* Variables and functions */
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double mp_time_sec () ; 
 scalar_t__ osd_query_and_reset_want_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_redraw (TYPE_2__*) ; 
 scalar_t__ vo_want_redraw (TYPE_2__*) ; 

__attribute__((used)) static void handle_osd_redraw(struct MPContext *mpctx)
{
    if (!mpctx->video_out || !mpctx->video_out->config_ok)
        return;
    // If we're playing normally, let OSD be redrawn naturally as part of
    // video display.
    if (!mpctx->paused) {
        if (mpctx->sleeptime < 0.1 && mpctx->video_status == STATUS_PLAYING)
            return;
    }
    // Don't redraw immediately during a seek (makes it significantly slower).
    bool use_video = mpctx->vo_chain && !mpctx->vo_chain->is_coverart;
    if (use_video && mp_time_sec() - mpctx->start_timestamp < 0.1) {
        mp_set_timeout(mpctx, 0.1);
        return;
    }
    bool want_redraw = osd_query_and_reset_want_redraw(mpctx->osd) ||
                       vo_want_redraw(mpctx->video_out);
    if (!want_redraw)
        return;
    vo_redraw(mpctx->video_out);
}