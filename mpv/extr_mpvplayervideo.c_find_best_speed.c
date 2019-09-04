#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct MPContext {int num_past_frames; TYPE_1__* opts; TYPE_2__* past_frames; } ;
struct TYPE_4__ {double approx_duration; } ;
struct TYPE_3__ {double playback_speed; } ;

/* Variables and functions */
 scalar_t__ calc_best_speed (double,double) ; 

__attribute__((used)) static double find_best_speed(struct MPContext *mpctx, double vsync)
{
    double total = 0;
    int num = 0;
    for (int n = 0; n < mpctx->num_past_frames; n++) {
        double dur = mpctx->past_frames[n].approx_duration;
        if (dur <= 0)
            continue;
        total += calc_best_speed(vsync, dur / mpctx->opts->playback_speed);
        num++;
    }
    return num > 0 ? total / num : 1;
}