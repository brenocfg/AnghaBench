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
struct demux_stream {int refreshing; int eof; struct demux_queue* queue; scalar_t__ global_correct_pos; scalar_t__ global_correct_dts; scalar_t__ selected; } ;
struct demux_queue {TYPE_1__* head; } ;
struct demux_internal {int num_streams; int force_metadata_update; TYPE_2__** streams; struct demux_cached_range* current_range; } ;
struct demux_cached_range {struct demux_queue** streams; } ;
struct TYPE_4__ {struct demux_stream* ds; } ;
struct TYPE_3__ {int /*<<< orphan*/  keyframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cached_range (struct demux_internal*,struct demux_cached_range*) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 int /*<<< orphan*/  remove_head_packet (struct demux_queue*) ; 
 int /*<<< orphan*/  set_current_range (struct demux_internal*,struct demux_cached_range*) ; 

__attribute__((used)) static void switch_current_range(struct demux_internal *in,
                                 struct demux_cached_range *range)
{
    struct demux_cached_range *old = in->current_range;
    assert(old != range);

    set_current_range(in, range);

    if (old) {
        // Remove packets which can't be used when seeking back to the range.
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_queue *queue = old->streams[n];

            // Remove all packets which cannot be involved in seeking.
            while (queue->head && !queue->head->keyframe)
                remove_head_packet(queue);
        }

        // Exclude weird corner cases that break resuming.
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *ds = in->streams[n]->ds;
            // This is needed to resume or join the range at all.
            if (ds->selected && !(ds->global_correct_dts ||
                                  ds->global_correct_pos))
            {
                MP_VERBOSE(in, "discarding unseekable range due to stream %d\n", n);
                clear_cached_range(in, old);
                break;
            }
        }
    }

    // Set up reading from new range (as well as writing to it).
    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;

        ds->queue = range->streams[n];
        ds->refreshing = false;
        ds->eof = false;
    }

    // No point in keeping any junk (especially if old current_range is empty).
    free_empty_cached_ranges(in);

    // The change detection doesn't work across ranges.
    in->force_metadata_update = true;
}