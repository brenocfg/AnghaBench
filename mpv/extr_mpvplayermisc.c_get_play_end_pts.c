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
struct TYPE_2__ {scalar_t__ type; } ;
struct MPOpts {scalar_t__* chapterrange; double* ab_loop; TYPE_1__ play_length; TYPE_1__ play_end; } ;
struct MPContext {scalar_t__ ab_loop_clip; struct MPOpts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double chapter_start_time (struct MPContext*,scalar_t__) ; 
 double get_ab_loop_start_time (struct MPContext*) ; 
 double get_play_start_pts (struct MPContext*) ; 
 double rel_time_to_abs (struct MPContext*,TYPE_1__) ; 

double get_play_end_pts(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    double end = MP_NOPTS_VALUE;
    if (opts->play_end.type) {
        end = rel_time_to_abs(mpctx, opts->play_end);
    }
    if (opts->play_length.type) {
        double start = get_play_start_pts(mpctx);
        if (start == MP_NOPTS_VALUE)
            start = 0;
        double length = rel_time_to_abs(mpctx, opts->play_length);
        if (length != MP_NOPTS_VALUE && (end == MP_NOPTS_VALUE || start + length < end))
            end = start + length;
    }
    if (opts->chapterrange[1] > 0) {
        double cend = chapter_start_time(mpctx, opts->chapterrange[1]);
        if (cend != MP_NOPTS_VALUE && (end == MP_NOPTS_VALUE || cend < end))
            end = cend;
    }
    // even though MP_NOPTS_VALUE is currently negative
    // it doesn't necessarily have to remain that way
    double ab_loop_start_time = get_ab_loop_start_time(mpctx);
    if (mpctx->ab_loop_clip && opts->ab_loop[1] != MP_NOPTS_VALUE &&
        (ab_loop_start_time == MP_NOPTS_VALUE || opts->ab_loop[1] > ab_loop_start_time))
    {
        if (end == MP_NOPTS_VALUE || end > opts->ab_loop[1])
            end = opts->ab_loop[1];
    }
    return end;
}