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
struct MPContext {int ab_loop_clip; double play_dir; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 scalar_t__ get_ab_loop_times (struct MPContext*,double*) ; 
 double get_current_time (struct MPContext*) ; 

void update_ab_loop_clip(struct MPContext *mpctx)
{
    double pts = get_current_time(mpctx);
    double ab[2];
    mpctx->ab_loop_clip = pts != MP_NOPTS_VALUE &&
                          get_ab_loop_times(mpctx, ab) &&
                          pts * mpctx->play_dir <= ab[1] * mpctx->play_dir;
}