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
struct MPContext {scalar_t__ ab_loop_clip; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 scalar_t__ get_ab_loop_times (struct MPContext*,double*) ; 
 double get_play_end_pts_setting (struct MPContext*) ; 

double get_play_end_pts(struct MPContext *mpctx)
{
    double end = get_play_end_pts_setting(mpctx);
    double ab[2];
    if (mpctx->ab_loop_clip && get_ab_loop_times(mpctx, ab)) {
        if (end == MP_NOPTS_VALUE || end > ab[1])
            end = ab[1];
    }
    return end;
}