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
struct MPContext {double video_pts; scalar_t__ video_status; TYPE_1__* seek_slave; } ;
struct TYPE_2__ {int /*<<< orphan*/  demuxer; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 scalar_t__ STATUS_EOF ; 
 int /*<<< orphan*/  demux_block_reading (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  demux_seek (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 double get_track_seek_offset (struct MPContext*,TYPE_1__*) ; 

__attribute__((used)) static void handle_delayed_audio_seek(struct MPContext *mpctx)
{
    if (mpctx->seek_slave) {
        if (mpctx->video_pts != MP_NOPTS_VALUE) {
            // We know the video position now, so seek external audio to the
            // correct position.
            double pts = mpctx->video_pts +
                            get_track_seek_offset(mpctx, mpctx->seek_slave);
            demux_seek(mpctx->seek_slave->demuxer, pts, 0);
            mpctx->seek_slave = NULL;
        } else if (mpctx->video_status >= STATUS_EOF) {
            // We won't get a video position; don't stall the audio stream.
            demux_block_reading(mpctx->seek_slave->demuxer, false);
            mpctx->seek_slave = NULL;
        }
    }
}