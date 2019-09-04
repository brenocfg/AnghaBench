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
struct sh_stream {int /*<<< orphan*/  index; struct demux_stream* ds; } ;
struct demuxer {struct demux_internal* in; } ;
struct demux_stream {int selected; } ;
struct demux_internal {int tracks_switched; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; scalar_t__ threading; int /*<<< orphan*/  ts_offset; int /*<<< orphan*/  initial_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ADD_PTS (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_trackswitch (struct demux_internal*) ; 
 int /*<<< orphan*/  initiate_refresh_seek (struct demux_internal*,struct demux_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_stream_selection_state (struct demux_internal*,struct demux_stream*) ; 

void demuxer_select_track(struct demuxer *demuxer, struct sh_stream *stream,
                          double ref_pts, bool selected)
{
    struct demux_internal *in = demuxer->in;
    struct demux_stream *ds = stream->ds;
    pthread_mutex_lock(&in->lock);
    // don't flush buffers if stream is already selected / unselected
    if (ds->selected != selected) {
        MP_VERBOSE(in, "%sselect track %d\n", selected ? "" : "de", stream->index);
        ds->selected = selected;
        update_stream_selection_state(in, ds);
        in->tracks_switched = true;
        if (ds->selected && !in->initial_state)
            initiate_refresh_seek(in, ds, MP_ADD_PTS(ref_pts, -in->ts_offset));
        if (in->threading) {
            pthread_cond_signal(&in->wakeup);
        } else {
            execute_trackswitch(in);
        }
    }
    pthread_mutex_unlock(&in->lock);
}