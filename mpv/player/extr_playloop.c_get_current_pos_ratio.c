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
struct demuxer {scalar_t__ filesize; scalar_t__ filepos; } ;
struct MPContext {double max_frames; TYPE_1__* opts; struct demuxer* demuxer; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ play_frames; } ;

/* Variables and functions */
 double MPCLAMP (double,int /*<<< orphan*/ ,int) ; 
 double MPMAX (double,double) ; 
 double get_current_time (struct MPContext*) ; 
 double get_play_end_pts (struct MPContext*) ; 
 double get_play_start_pts (struct MPContext*) ; 
 double get_time_length (struct MPContext*) ; 

double get_current_pos_ratio(struct MPContext *mpctx, bool use_range)
{
    struct demuxer *demuxer = mpctx->demuxer;
    if (!demuxer)
        return -1;
    double ans = -1;
    double start = 0;
    double len = get_time_length(mpctx);
    if (use_range) {
        double startpos = get_play_start_pts(mpctx);
        double endpos = get_play_end_pts(mpctx);
        if (endpos > MPMAX(0, len))
            endpos = MPMAX(0, len);
        if (endpos < startpos)
            endpos = startpos;
        start = startpos;
        len = endpos - startpos;
    }
    double pos = get_current_time(mpctx);
    if (len > 0)
        ans = MPCLAMP((pos - start) / len, 0, 1);
    if (ans < 0) {
        int64_t size = demuxer->filesize;
        if (size > 0 && demuxer->filepos >= 0)
            ans = MPCLAMP(demuxer->filepos / (double)size, 0, 1);
    }
    if (use_range) {
        if (mpctx->opts->play_frames > 0)
            ans = MPMAX(ans, 1.0 -
                    mpctx->max_frames / (double) mpctx->opts->play_frames);
    }
    return ans;
}