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
struct demux_stream {int /*<<< orphan*/  selected; int /*<<< orphan*/  refreshing; scalar_t__ fw_bytes; scalar_t__ eager; scalar_t__ global_correct_pos; scalar_t__ global_correct_dts; } ;
struct demux_queue {int num_index; int /*<<< orphan*/ * index; struct demux_packet* keyframe_latest; int /*<<< orphan*/ * next_prune_target; struct demux_packet* tail; struct demux_packet* head; int /*<<< orphan*/  is_eof; int /*<<< orphan*/  keyframe_end_pts; int /*<<< orphan*/  keyframe_pts; int /*<<< orphan*/  last_ts; int /*<<< orphan*/  last_dts; int /*<<< orphan*/  last_pos; int /*<<< orphan*/  correct_pos; int /*<<< orphan*/  correct_dts; int /*<<< orphan*/  seek_end; } ;
struct demux_packet {scalar_t__ dts; scalar_t__ pos; scalar_t__ pts; scalar_t__ len; struct demux_packet* next; int /*<<< orphan*/  kf_seek_pts; } ;
struct demux_internal {int num_ranges; int num_streams; int seeking; double seek_pts; int /*<<< orphan*/  seek_flags; struct demux_cached_range* current_range; scalar_t__ fw_bytes; TYPE_1__** streams; struct demux_cached_range** ranges; } ;
struct demux_cached_range {scalar_t__ seek_start; double seek_end; struct demux_queue** streams; } ;
struct TYPE_2__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double INFINITY ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct demux_internal*,char*,int) ; 
 int /*<<< orphan*/  SEEK_HR ; 
 int /*<<< orphan*/  add_index_entry (struct demux_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cached_range (struct demux_internal*,struct demux_cached_range*) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 int /*<<< orphan*/  recompute_buffers (struct demux_stream*) ; 
 int /*<<< orphan*/  remove_head_packet (struct demux_queue*) ; 
 int /*<<< orphan*/  update_seek_ranges (struct demux_cached_range*) ; 

__attribute__((used)) static void attempt_range_joining(struct demux_internal *in)
{
    struct demux_cached_range *next = NULL;
    double next_dist = INFINITY;

    assert(in->current_range && in->num_ranges > 0);
    assert(in->current_range == in->ranges[in->num_ranges - 1]);

    for (int n = 0; n < in->num_ranges - 1; n++) {
        struct demux_cached_range *range = in->ranges[n];

        if (in->current_range->seek_start <= range->seek_start) {
            // This uses ">" to get some non-0 overlap.
            double dist = in->current_range->seek_end - range->seek_start;
            if (dist > 0 && dist < next_dist) {
                next = range;
                next_dist = dist;
            }
        }
    }

    if (!next)
        return;

    MP_VERBOSE(in, "going to join ranges %f-%f + %f-%f\n",
               in->current_range->seek_start, in->current_range->seek_end,
               next->seek_start, next->seek_end);

    // Try to find a join point, where packets obviously overlap. (It would be
    // better and faster to do this incrementally, but probably too complex.)
    // The current range can overlap arbitrarily with the next one, not only by
    // by the seek overlap, but for arbitrary packet readahead as well.
    // We also drop the overlapping packets (if joining fails, we discard the
    // entire next range anyway, so this does no harm).
    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;

        struct demux_queue *q1 = in->current_range->streams[n];
        struct demux_queue *q2 = next->streams[n];

        if (!ds->global_correct_pos && !ds->global_correct_dts) {
            MP_WARN(in, "stream %d: ranges unjoinable\n", n);
            goto failed;
        }

        struct demux_packet *end = q1->tail;
        bool join_point_found = !end; // no packets yet -> joining will work
        if (end) {
            while (q2->head) {
                struct demux_packet *dp = q2->head;

                // Some weird corner-case. We'd have to search the equivalent
                // packet in q1 to update it correctly. Better just give up.
                if (dp == q2->keyframe_latest) {
                    MP_VERBOSE(in, "stream %d: not enough keyframes for join\n", n);
                    goto failed;
                }

                if ((ds->global_correct_dts && dp->dts == end->dts) ||
                    (ds->global_correct_pos && dp->pos == end->pos))
                {
                    // Do some additional checks as a (imperfect) sanity check
                    // in case pos/dts are not "correct" across the ranges (we
                    // never actually check that).
                    if (dp->dts != end->dts || dp->pos != end->pos ||
                        dp->pts != end->pts || dp->len != end->len)
                    {
                        MP_WARN(in, "stream %d: weird demuxer behavior\n", n);
                        goto failed;
                    }

                    // q1 usually meets q2 at a keyframe. q1 will end on a key-
                    // frame (because it tries joining when reading a keyframe).
                    // Obviously, q1 can not know the kf_seek_pts yet; it would
                    // have to read packets after it to compute it. Ideally,
                    // we'd remove it and use q2's packet, but the linked list
                    // makes this hard, so copy this missing metadata instead.
                    end->kf_seek_pts = dp->kf_seek_pts;

                    remove_head_packet(q2);
                    join_point_found = true;
                    break;
                }

                // This happens if the next range misses the end packet. For
                // normal streams (ds->eager==true), this is a failure to find
                // an overlap. For subtitles, this can mean the current_range
                // has a subtitle somewhere before the end of its range, and
                // next has another subtitle somewhere after the start of its
                // range.
                if ((ds->global_correct_dts && dp->dts > end->dts) ||
                    (ds->global_correct_pos && dp->pos > end->pos))
                    break;

                remove_head_packet(q2);
            }
        }

        // For enabled non-sparse streams, always require an overlap packet.
        if (ds->eager && !join_point_found) {
            MP_WARN(in, "stream %d: no joint point found\n", n);
            goto failed;
        }
    }

    // Actually join the ranges. Now that we think it will work, mutate the
    // data associated with the current range.

    in->fw_bytes = 0;

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_queue *q1 = in->current_range->streams[n];
        struct demux_queue *q2 = next->streams[n];

        struct demux_stream *ds = in->streams[n]->ds;

        if (q2->head) {
            if (q1->head) {
                q1->tail->next = q2->head;
            } else {
                q1->head = q2->head;
            }
            q1->tail = q2->tail;
        }

        q1->seek_end = q2->seek_end;
        q1->correct_dts &= q2->correct_dts;
        q1->correct_pos &= q2->correct_pos;
        q1->last_pos = q2->last_pos;
        q1->last_dts = q2->last_dts;
        q1->last_ts = q2->last_ts;
        q1->keyframe_pts = q2->keyframe_pts;
        q1->keyframe_end_pts = q2->keyframe_end_pts;
        q1->keyframe_latest = q2->keyframe_latest;
        q1->is_eof = q2->is_eof;

        q2->head = q2->tail = NULL;
        q2->next_prune_target = NULL;
        q2->keyframe_latest = NULL;

        for (int i = 0; i < q2->num_index; i++)
            add_index_entry(q1, q2->index[i]);
        q2->num_index = 0;

        recompute_buffers(ds);
        in->fw_bytes += ds->fw_bytes;

        // For moving demuxer position.
        ds->refreshing = ds->selected;
    }

    update_seek_ranges(in->current_range);

    // Move demuxing position to after the current range.
    in->seeking = true;
    in->seek_flags = SEEK_HR;
    in->seek_pts = next->seek_end - 1.0;

    MP_VERBOSE(in, "ranges joined!\n");

failed:
    clear_cached_range(in, next);
    free_empty_cached_ranges(in);
}