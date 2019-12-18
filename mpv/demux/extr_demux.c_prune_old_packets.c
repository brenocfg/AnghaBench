#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct demux_stream {size_t index; TYPE_2__* sh; struct demux_packet* reader_head; } ;
struct demux_queue {double seek_start; double last_pruned; struct demux_packet* keyframe_first; struct demux_packet* head; struct demux_stream* ds; } ;
struct demux_packet {struct demux_packet* next; scalar_t__ keyframe; } ;
struct demux_internal {int num_ranges; int num_streams; scalar_t__ max_bytes_bw; scalar_t__ max_bytes; scalar_t__ total_bytes; struct demux_cached_range* current_range; scalar_t__ seekable_cache; struct demux_cached_range** ranges; TYPE_1__** streams; } ;
struct demux_cached_range {int num_streams; double seek_start; struct demux_queue** streams; } ;
struct TYPE_4__ {scalar_t__ seek_preroll; } ;
struct TYPE_3__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_keyframe_times (struct demux_packet*,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 scalar_t__ get_foward_buffered_bytes (struct demux_stream*) ; 
 int /*<<< orphan*/  remove_head_packet (struct demux_queue*) ; 
 int /*<<< orphan*/  update_seek_ranges (struct demux_cached_range*) ; 

__attribute__((used)) static void prune_old_packets(struct demux_internal *in)
{
    assert(in->current_range == in->ranges[in->num_ranges - 1]);

    // It's not clear what the ideal way to prune old packets is. For now, we
    // prune the oldest packet runs, as long as the total cache amount is too
    // big.
    while (1) {
        uint64_t fw_bytes = 0;
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;
            fw_bytes += get_foward_buffered_bytes(ds);
        }
        uint64_t max_avail = in->max_bytes_bw;
        // Backward cache (if enabled at all) can use unused forward cache.
        // Still leave 1 byte free, so the read_packet logic doesn't get stuck.
        if (max_avail && in->max_bytes > (fw_bytes + 1))
            max_avail += in->max_bytes - (fw_bytes + 1);
        if (in->total_bytes - fw_bytes <= max_avail)
            break;

        // (Start from least recently used range.)
        struct demux_cached_range *range = in->ranges[0];
        double earliest_ts = MP_NOPTS_VALUE;
        struct demux_stream *earliest_stream = NULL;

        for (int n = 0; n < range->num_streams; n++) {
            struct demux_queue *queue = range->streams[n];
            struct demux_stream *ds = queue->ds;

            if (queue->head && queue->head != ds->reader_head) {
                struct demux_packet *dp = queue->head;
                double ts = queue->seek_start;
                // If the ts is NOPTS, the queue has no retainable packets, so
                // delete them all. This code is not run when there's enough
                // free space, so normally the queue gets the chance to build up.
                bool prune_always =
                    !in->seekable_cache || ts == MP_NOPTS_VALUE || !dp->keyframe;
                if (prune_always || !earliest_stream || ts < earliest_ts) {
                    earliest_ts = ts;
                    earliest_stream = ds;
                    if (prune_always)
                        break;
                }
            }
        }

        // In some cases (like when the seek index became huge), there aren't
        // any backwards packets, even if the total cache size is exceeded.
        if (!earliest_stream)
            break;

        struct demux_stream *ds = earliest_stream;
        struct demux_queue *queue = range->streams[ds->index];

        bool non_kf_prune = queue->head && !queue->head->keyframe;
        bool kf_was_pruned = false;

        while (queue->head && queue->head != ds->reader_head) {
            if (queue->head->keyframe) {
                // If the cache is seekable, only delete until up the next
                // keyframe. This is not always efficient, but ensures we
                // prune all streams fairly.
                // Also, if the first packet was _not_ a keyframe, we want it
                // to remove all preceding non-keyframe packets first, before
                // re-evaluating what to prune next.
                if ((kf_was_pruned || non_kf_prune) && in->seekable_cache)
                    break;
                kf_was_pruned = true;
            }

            remove_head_packet(queue);
        }

        // Need to update the seekable time range.
        if (kf_was_pruned) {
            assert(!queue->keyframe_first); // it was just deleted, supposedly

            queue->keyframe_first = queue->head;
            // (May happen if reader_head stopped pruning the range, and there's
            // no next range.)
            while (queue->keyframe_first && !queue->keyframe_first->keyframe)
                queue->keyframe_first = queue->keyframe_first->next;

            if (queue->seek_start != MP_NOPTS_VALUE)
                queue->last_pruned = queue->seek_start;

            double kf_min;
            compute_keyframe_times(queue->keyframe_first, &kf_min, NULL);

            bool update_range = true;

            queue->seek_start = kf_min;

            if (queue->seek_start != MP_NOPTS_VALUE) {
                queue->seek_start += ds->sh->seek_preroll;

                // Don't need to update if the new start is still before the
                // range's start (or if the range was undefined anyway).
                if (range->seek_start == MP_NOPTS_VALUE ||
                    queue->seek_start <= range->seek_start)
                {
                    update_range = false;
                }
            }

            if (update_range)
                update_seek_ranges(range);
        }

        if (range != in->current_range && range->seek_start == MP_NOPTS_VALUE)
            free_empty_cached_ranges(in);
    }
}