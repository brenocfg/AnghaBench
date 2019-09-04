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
struct demux_stream {scalar_t__ type; int skip_to_keyframe; scalar_t__ selected; scalar_t__ refreshing; scalar_t__ fw_bytes; struct demux_packet* reader_head; int /*<<< orphan*/  base_ts; } ;
struct demux_queue {int dummy; } ;
struct demux_packet {double kf_seek_pts; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
struct demux_internal {int num_streams; int seeking; int seek_flags; TYPE_1__** streams; scalar_t__ seek_pts; struct demux_cached_range* current_range; int /*<<< orphan*/  fw_bytes; } ;
struct demux_cached_range {scalar_t__ seek_end; struct demux_queue** streams; } ;
struct TYPE_2__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,...) ; 
 int /*<<< orphan*/  PTS_OR_DEF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SEEK_FORWARD ; 
 int SEEK_HR ; 
 scalar_t__ STREAM_VIDEO ; 
 struct demux_packet* find_seek_target (struct demux_queue*,double,int) ; 
 int /*<<< orphan*/  recompute_buffers (struct demux_stream*) ; 
 int /*<<< orphan*/  stream_type_name (scalar_t__) ; 
 int /*<<< orphan*/  switch_current_range (struct demux_internal*,struct demux_cached_range*) ; 

__attribute__((used)) static void execute_cache_seek(struct demux_internal *in,
                               struct demux_cached_range *range,
                               double pts, int flags)
{
    // Adjust the seek target to the found video key frames. Otherwise the
    // video will undershoot the seek target, while audio will be closer to it.
    // The player frontend will play the additional video without audio, so
    // you get silent audio for the amount of "undershoot". Adjusting the seek
    // target will make the audio seek to the video target or before.
    // (If hr-seeks are used, it's better to skip this, as it would only mean
    // that more audio data than necessary would have to be decoded.)
    if (!(flags & SEEK_HR)) {
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;
            struct demux_queue *queue = range->streams[n];
            if (ds->selected && ds->type == STREAM_VIDEO) {
                struct demux_packet *target = find_seek_target(queue, pts, flags);
                if (target) {
                    double target_pts = target->kf_seek_pts;
                    if (target_pts != MP_NOPTS_VALUE) {
                        MP_VERBOSE(in, "adjust seek target %f -> %f\n",
                                   pts, target_pts);
                        // (We assume the find_seek_target() will return the
                        // same target for the video stream.)
                        pts = target_pts;
                        flags &= ~SEEK_FORWARD;
                    }
                }
                break;
            }
        }
    }

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;
        struct demux_queue *queue = range->streams[n];

        struct demux_packet *target = find_seek_target(queue, pts, flags);
        ds->reader_head = target;
        ds->skip_to_keyframe = !target;
        if (ds->reader_head)
            ds->base_ts = PTS_OR_DEF(ds->reader_head->pts, ds->reader_head->dts);

        recompute_buffers(ds);
        in->fw_bytes += ds->fw_bytes;

        MP_VERBOSE(in, "seeking stream %d (%s) to ",
                   n, stream_type_name(ds->type));

        if (target) {
            MP_VERBOSE(in, "packet %f/%f\n", target->pts, target->dts);
        } else {
            MP_VERBOSE(in, "nothing\n");
        }
    }

    // If we seek to another range, we want to seek the low level demuxer to
    // there as well, because reader and demuxer queue must be the same.
    if (in->current_range != range) {
        switch_current_range(in, range);

        in->seeking = true;
        in->seek_flags = SEEK_HR;
        in->seek_pts = range->seek_end - 1.0;

        // When new packets are being appended, they could overlap with the old
        // range due to demuxer seek imprecisions, or because the queue contains
        // packets past the seek target but before the next seek target. Don't
        // append them twice, instead skip them until new packets are found.
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;

            ds->refreshing = ds->selected;
        }

        MP_VERBOSE(in, "resuming demuxer to end of cached range\n");
    }
}