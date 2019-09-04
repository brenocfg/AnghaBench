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
struct MPOpts {scalar_t__* chapterrange; int /*<<< orphan*/  rebase_start_time; int /*<<< orphan*/  play_start; } ;
struct MPContext {TYPE_1__* demuxer; struct MPOpts* opts; } ;
struct TYPE_2__ {scalar_t__ start_time; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double chapter_start_time (struct MPContext*,scalar_t__) ; 
 double rel_time_to_abs (struct MPContext*,int /*<<< orphan*/ ) ; 

double get_play_start_pts(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    double play_start_pts = rel_time_to_abs(mpctx, opts->play_start);
    if (play_start_pts == MP_NOPTS_VALUE && opts->chapterrange[0] > 0) {
        double chapter_start_pts = chapter_start_time(mpctx, opts->chapterrange[0] - 1);
        if (chapter_start_pts != MP_NOPTS_VALUE) {
            /*
             * get_play_start_pts always returns rebased timetamps,
             * even with --rebase-start-time=no. chapter_start_time
             * values are not rebased without --rebase-start-time=yes,
             * so we need to rebase them here to be consistent with
             * the rest of get_play_start_pts.
             */
            if (mpctx->demuxer && !mpctx->opts->rebase_start_time){
                chapter_start_pts -= mpctx->demuxer->start_time;
            }
            play_start_pts = chapter_start_pts;
        }
    }
    return play_start_pts;
}