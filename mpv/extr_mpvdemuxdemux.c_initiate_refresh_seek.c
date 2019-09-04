#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct demuxer {int /*<<< orphan*/  partially_seekable; int /*<<< orphan*/  seekable; TYPE_1__* desc; } ;
struct demux_stream {scalar_t__ type; int last_ret_pos; double last_ret_dts; int refreshing; TYPE_3__* queue; scalar_t__ selected; int /*<<< orphan*/  base_ts; } ;
struct demux_internal {int num_streams; int seeking; double seek_pts; int /*<<< orphan*/  seek_flags; int /*<<< orphan*/  current_range; TYPE_2__** streams; struct demuxer* d_thread; } ;
struct TYPE_6__ {int correct_dts; int correct_pos; int last_pos; double last_dts; } ;
struct TYPE_5__ {struct demux_stream* ds; } ;
struct TYPE_4__ {scalar_t__ seek; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double MP_PTS_MIN (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,...) ; 
 int /*<<< orphan*/  SEEK_HR ; 
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  clear_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  ds_clear_reader_queue_state (struct demux_stream*) ; 
 int /*<<< orphan*/  update_seek_ranges (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initiate_refresh_seek(struct demux_internal *in,
                                  struct demux_stream *stream,
                                  double start_ts)
{
    struct demuxer *demux = in->d_thread;
    bool seekable = demux->desc->seek && demux->seekable &&
                    !demux->partially_seekable;

    bool normal_seek = true;
    bool refresh_possible = true;
    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;

        if (!ds->selected)
            continue;

        if (ds->type == STREAM_VIDEO || ds->type == STREAM_AUDIO)
            start_ts = MP_PTS_MIN(start_ts, ds->base_ts);

        // If there were no other streams selected, we can use a normal seek.
        normal_seek &= stream == ds;

        refresh_possible &= ds->queue->correct_dts || ds->queue->correct_pos;
    }

    if (start_ts == MP_NOPTS_VALUE || !seekable)
        return;

    if (!normal_seek) {
        if (!refresh_possible) {
            MP_VERBOSE(in, "can't issue refresh seek\n");
            return;
        }

        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;

            bool correct_pos = ds->queue->correct_pos;
            bool correct_dts = ds->queue->correct_dts;

            // We need to re-read all packets anyway, so discard the buffered
            // data. (In theory, we could keep the packets, and be able to use
            // it for seeking if partially read streams are deselected again,
            // but this causes other problems like queue overflows when
            // selecting a new stream.)
            ds_clear_reader_queue_state(ds);
            clear_queue(ds->queue);

            // Streams which didn't have any packets yet will return all packets,
            // other streams return packets only starting from the last position.
            if (ds->selected && (ds->last_ret_pos != -1 ||
                                 ds->last_ret_dts != MP_NOPTS_VALUE))
            {
                ds->refreshing = true;
                ds->queue->correct_dts = correct_dts;
                ds->queue->correct_pos = correct_pos;
                ds->queue->last_pos = ds->last_ret_pos;
                ds->queue->last_dts = ds->last_ret_dts;
            }

            update_seek_ranges(in->current_range);
        }

        start_ts -= 1.0; // small offset to get correct overlap
    }

    MP_VERBOSE(in, "refresh seek to %f\n", start_ts);
    in->seeking = true;
    in->seek_flags = SEEK_HR;
    in->seek_pts = start_ts;
}