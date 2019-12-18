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
struct demux_stream {int eof; int refreshing; int eager; int selected; scalar_t__ type; size_t index; int /*<<< orphan*/  still_image; TYPE_1__* sh; } ;
struct demux_internal {int num_streams; int blocked; int num_ranges; struct demux_cached_range** ranges; TYPE_2__** streams; } ;
struct demux_cached_range {int /*<<< orphan*/ * streams; } ;
struct TYPE_4__ {struct demux_stream* ds; } ;
struct TYPE_3__ {int /*<<< orphan*/  attached_picture; int /*<<< orphan*/  still_image; } ;

/* Variables and functions */
 scalar_t__ STREAM_SUB ; 
 int /*<<< orphan*/  clear_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_clear_reader_state (struct demux_stream*,int) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 int /*<<< orphan*/  update_seek_ranges (struct demux_cached_range*) ; 
 int /*<<< orphan*/  wakeup_ds (struct demux_stream*) ; 

__attribute__((used)) static void update_stream_selection_state(struct demux_internal *in,
                                          struct demux_stream *ds)
{
    ds->eof = false;
    ds->refreshing = false;

    // We still have to go over the whole stream list to update ds->eager for
    // other streams too, because they depend on other stream's selections.

    bool any_av_streams = false;
    bool any_streams = false;

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *s = in->streams[n]->ds;

        s->still_image = s->sh->still_image;
        s->eager = s->selected && !s->sh->attached_picture;
        if (s->eager && !s->still_image)
            any_av_streams |= s->type != STREAM_SUB;
        any_streams |= s->selected;
    }

    // Subtitles are only eagerly read if there are no other eagerly read
    // streams.
    if (any_av_streams) {
        for (int n = 0; n < in->num_streams; n++) {
            struct demux_stream *s = in->streams[n]->ds;

            if (s->type == STREAM_SUB)
                s->eager = false;
        }
    }

    if (!any_streams)
        in->blocked = false;

    ds_clear_reader_state(ds, true);

    // Make sure any stream reselection or addition is reflected in the seek
    // ranges, and also get rid of data that is not needed anymore (or
    // rather, which can't be kept consistent). This has to happen after we've
    // updated all the subtle state (like s->eager).
    for (int n = 0; n < in->num_ranges; n++) {
        struct demux_cached_range *range = in->ranges[n];

        if (!ds->selected)
            clear_queue(range->streams[ds->index]);

        update_seek_ranges(range);
    }

    free_empty_cached_ranges(in);

    wakeup_ds(ds);
}