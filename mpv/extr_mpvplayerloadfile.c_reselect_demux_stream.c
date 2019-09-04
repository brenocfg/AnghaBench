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
struct track {scalar_t__ type; int /*<<< orphan*/  selected; int /*<<< orphan*/  stream; int /*<<< orphan*/  demuxer; } ;
struct MPContext {struct track* seek_slave; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 scalar_t__ STREAM_SUB ; 
 int /*<<< orphan*/  demuxer_select_track (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 double get_current_time (struct MPContext*) ; 
 scalar_t__ get_track_seek_offset (struct MPContext*,struct track*) ; 

void reselect_demux_stream(struct MPContext *mpctx, struct track *track)
{
    if (!track->stream)
        return;
    double pts = get_current_time(mpctx);
    if (pts != MP_NOPTS_VALUE) {
        pts += get_track_seek_offset(mpctx, track);
        if (track->type == STREAM_SUB)
            pts -= 10.0;
    }
    demuxer_select_track(track->demuxer, track->stream, pts, track->selected);
    if (track == mpctx->seek_slave)
        mpctx->seek_slave = NULL;
}