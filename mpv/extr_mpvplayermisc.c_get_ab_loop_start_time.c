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
struct MPOpts {double* ab_loop; } ;
struct MPContext {struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double get_play_start_pts (struct MPContext*) ; 

double get_ab_loop_start_time(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    double ab_loop_start_time;
    if (opts->ab_loop[0] != MP_NOPTS_VALUE) {
        ab_loop_start_time = opts->ab_loop[0];
    } else {
        /*
         * There is no check for MP_NOPTS_VALUE here
         * because that's exactly what we want to return
         * if get_play_start_pts comes up empty here.
         */
        ab_loop_start_time = get_play_start_pts(mpctx);
    }
    return ab_loop_start_time;
}