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
struct demuxer {struct demux_internal* in; } ;
struct demux_stream {size_t type; } ;
struct demux_queue {int dummy; } ;
struct demux_packet {struct demux_packet* next; scalar_t__ keyframe; int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
struct demux_internal {int num_streams; int /*<<< orphan*/  lock; int /*<<< orphan*/  ts_offset; TYPE_1__** streams; struct demuxer* d_user; } ;
struct demux_cached_range {double seek_start; struct demux_queue** streams; } ;
struct TYPE_2__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double MP_ADD_PTS (double,int /*<<< orphan*/ ) ; 
 double MP_NOPTS_VALUE ; 
 double MP_PTS_MAX (double,double) ; 
 double MP_PTS_OR_DEF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t STREAM_AUDIO ; 
 int STREAM_TYPE_COUNT ; 
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  adjust_cache_seek_target (struct demux_internal*,struct demux_cached_range*,double*,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_keyframe_times (struct demux_packet*,double*,int /*<<< orphan*/ *) ; 
 struct demux_cached_range* find_cache_seek_range (struct demux_internal*,double,int) ; 
 struct demux_packet* find_seek_target (struct demux_queue*,double,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

double demux_probe_cache_dump_target(struct demuxer *demuxer, double pts,
                                     bool for_end)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    double res = MP_NOPTS_VALUE;
    if (pts == MP_NOPTS_VALUE)
        return pts;

    pthread_mutex_lock(&in->lock);

    pts = MP_ADD_PTS(pts, -in->ts_offset);

    // (When determining the end, look before the keyframe at pts, so subtract
    // an arbitrary amount to round down.)
    double seek_pts = for_end ? pts - 0.001 : pts;
    int flags = 0;
    struct demux_cached_range *r = find_cache_seek_range(in, seek_pts, flags);
    if (r) {
        if (!for_end)
            adjust_cache_seek_target(in, r, &pts, &flags);

        double t[STREAM_TYPE_COUNT];
        for (int n = 0; n < STREAM_TYPE_COUNT; n++)
            t[n] = MP_NOPTS_VALUE;

        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;
            struct demux_queue *q = r->streams[n];

            struct demux_packet *dp = find_seek_target(q, pts, flags);
            if (dp) {
                if (for_end) {
                    while (dp) {
                        double pdts = MP_PTS_OR_DEF(dp->dts, dp->pts);

                        if (pdts != MP_NOPTS_VALUE && pdts >= pts && dp->keyframe)
                            break;

                        t[ds->type] = MP_PTS_MAX(t[ds->type], pdts);

                        dp = dp->next;
                    }
                } else {
                    double start;
                    compute_keyframe_times(dp, &start, NULL);
                    start = MP_PTS_MAX(start, r->seek_start);
                    t[ds->type] = MP_PTS_MAX(t[ds->type], start);
                }
            }
        }

        res = t[STREAM_VIDEO];
        if (res == MP_NOPTS_VALUE)
            res = t[STREAM_AUDIO];
        if (res == MP_NOPTS_VALUE) {
            for (int n = 0; n < STREAM_TYPE_COUNT; n++) {
                res = t[n];
                if (res != MP_NOPTS_VALUE)
                    break;
            }
        }
    }

    res = MP_ADD_PTS(res, in->ts_offset);

    pthread_mutex_unlock(&in->lock);

    return res;
}