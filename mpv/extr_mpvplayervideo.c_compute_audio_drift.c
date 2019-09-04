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
struct frame_info {double num_vsyncs; double av_diff; } ;
struct MPContext {int num_past_frames; struct frame_info* past_frames; } ;

/* Variables and functions */
 double NAN ; 

__attribute__((used)) static double compute_audio_drift(struct MPContext *mpctx, double vsync)
{
    // Least-squares linear regression, using relative real time for x, and
    // audio desync for y. Assume speed didn't change for the frames we're
    // looking at for simplicity. This also should actually use the realtime
    // (minus paused time) for x, but use vsync scheduling points instead.
    if (mpctx->num_past_frames <= 10)
        return NAN;
    int num = mpctx->num_past_frames - 1;
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;
    double x = 0;
    for (int n = 0; n < num; n++) {
        struct frame_info *frame = &mpctx->past_frames[n + 1];
        if (frame->num_vsyncs < 0)
            return NAN;
        double y = frame->av_diff;
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_xx += x * x;
        x -= frame->num_vsyncs * vsync;
    }
    return (sum_x * sum_y - num * sum_xy) / (sum_x * sum_x - num * sum_xx);
}