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
struct vo_chain {TYPE_1__* filter; } ;
struct MPContext {int num_past_frames; int num_next_frames; TYPE_3__* past_frames; TYPE_2__** next_frames; struct vo_chain* vo_chain; } ;
struct TYPE_6__ {double duration; double approx_duration; } ;
struct TYPE_5__ {double pts; } ;
struct TYPE_4__ {double container_fps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPMAX (int /*<<< orphan*/ ,double) ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_STATS (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 double fabs (double) ; 

__attribute__((used)) static void calculate_frame_duration(struct MPContext *mpctx)
{
    struct vo_chain *vo_c = mpctx->vo_chain;
    assert(mpctx->num_past_frames >= 1 && mpctx->num_next_frames >= 1);

    double demux_duration = vo_c->filter->container_fps > 0
                            ? 1.0 / vo_c->filter->container_fps : -1;
    double duration = demux_duration;

    if (mpctx->num_next_frames >= 2) {
        double pts0 = mpctx->next_frames[0]->pts;
        double pts1 = mpctx->next_frames[1]->pts;
        if (pts0 != MP_NOPTS_VALUE && pts1 != MP_NOPTS_VALUE && pts1 >= pts0)
            duration = pts1 - pts0;
    }

    // The following code tries to compensate for rounded Matroska timestamps
    // by "unrounding" frame durations, or if not possible, approximating them.
    // These formats usually round on 1ms. Some muxers do this incorrectly,
    // and might go off by 1ms more, and compensate for it later by an equal
    // rounding error into the opposite direction.
    double tolerance = 0.001 * 3 + 0.0001;

    double total = 0;
    int num_dur = 0;
    for (int n = 1; n < mpctx->num_past_frames; n++) {
        // Eliminate likely outliers using a really dumb heuristic.
        double dur = mpctx->past_frames[n].duration;
        if (dur <= 0 || fabs(dur - duration) >= tolerance)
            break;
        total += dur;
        num_dur += 1;
    }
    double approx_duration = num_dur > 0 ? total / num_dur : duration;

    // Try if the demuxer frame rate fits - if so, just take it.
    if (demux_duration > 0) {
        // Note that even if each timestamp is within rounding tolerance, it
        // could literally not add up (e.g. if demuxer FPS is rounded itself).
        if (fabs(duration - demux_duration) < tolerance &&
            fabs(total - demux_duration * num_dur) < tolerance &&
            (num_dur >= 16 || num_dur >= mpctx->num_past_frames - 4))
        {
            approx_duration = demux_duration;
        }
    }

    mpctx->past_frames[0].duration = duration;
    mpctx->past_frames[0].approx_duration = approx_duration;

    MP_STATS(mpctx, "value %f frame-duration", MPMAX(0, duration));
    MP_STATS(mpctx, "value %f frame-duration-approx", MPMAX(0, approx_duration));
}