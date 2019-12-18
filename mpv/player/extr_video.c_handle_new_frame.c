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
struct MPContext {int num_next_frames; double video_pts; double delay; scalar_t__ video_status; double time_frame; double video_speed; TYPE_3__* demuxer; TYPE_2__* vo_chain; TYPE_1__** next_frames; } ;
struct TYPE_6__ {scalar_t__ ts_resets_possible; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_sparse; } ;
struct TYPE_4__ {double pts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TRACE (struct MPContext*,char*,double) ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*,double,double) ; 
 scalar_t__ STATUS_PLAYING ; 
 int /*<<< orphan*/  adjust_sync (struct MPContext*,double,double) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void handle_new_frame(struct MPContext *mpctx)
{
    assert(mpctx->num_next_frames >= 1);

    double frame_time = 0;
    double pts = mpctx->next_frames[0]->pts;
    bool is_sparse = mpctx->vo_chain && mpctx->vo_chain->is_sparse;

    if (mpctx->video_pts != MP_NOPTS_VALUE) {
        frame_time = pts - mpctx->video_pts;
        double tolerance = mpctx->demuxer->ts_resets_possible &&
                           !is_sparse ? 5 : 1e4;
        if (frame_time <= 0 || frame_time >= tolerance) {
            // Assume a discontinuity.
            MP_WARN(mpctx, "Invalid video timestamp: %f -> %f\n",
                    mpctx->video_pts, pts);
            frame_time = 0;
        }
    }
    mpctx->delay -= frame_time;
    if (mpctx->video_status >= STATUS_PLAYING) {
        mpctx->time_frame += frame_time / mpctx->video_speed;
        adjust_sync(mpctx, pts, frame_time);
    }
    MP_TRACE(mpctx, "frametime=%5.3f\n", frame_time);
}