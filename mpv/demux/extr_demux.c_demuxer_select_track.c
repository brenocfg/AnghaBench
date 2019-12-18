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
struct demux_stream {int selected; double back_seek_pos; } ;
struct demux_internal {int tracks_switched; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; scalar_t__ threading; int /*<<< orphan*/  after_seek; scalar_t__ back_demuxing; int /*<<< orphan*/  ts_offset; } ;

/* Variables and functions */
 double MP_ADD_PTS (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_trackswitch (struct demux_internal*) ; 
 int /*<<< orphan*/  initiate_refresh_seek (struct demux_internal*,struct demux_stream*,double) ; 
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
    ref_pts = MP_ADD_PTS(ref_pts, -in->ts_offset);
    // don't flush buffers if stream is already selected / unselected
    if (ds->selected != selected) {
        MP_VERBOSE(in, "%sselect track %d\n", selected ? "" : "de", stream->index);
        ds->selected = selected;
        update_stream_selection_state(in, ds);
        in->tracks_switched = true;
        if (ds->selected) {
            if (in->back_demuxing)
                ds->back_seek_pos = ref_pts;
            if (!in->after_seek)
                initiate_refresh_seek(in, ds, ref_pts);
        }
        if (in->threading) {
            pthread_cond_signal(&in->wakeup);
        } else {
            execute_trackswitch(in);
        }
    }
    pthread_mutex_unlock(&in->lock);
}