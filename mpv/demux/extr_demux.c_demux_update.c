#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timed_metadata {int dummy; } ;
struct demux_internal {double last_playback_pts; int force_metadata_update; int events; int /*<<< orphan*/  lock; int /*<<< orphan*/  duration; int /*<<< orphan*/  ts_offset; int /*<<< orphan*/  threading; TYPE_1__* d_user; } ;
struct TYPE_5__ {int events; int /*<<< orphan*/  duration; struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int DEMUX_EVENT_DURATION ; 
 int DEMUX_EVENT_METADATA ; 
 int DEMUX_EVENT_STREAMS ; 
 double MP_ADD_PTS (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_update_replaygain (TYPE_1__*) ; 
 struct timed_metadata* lookup_timed_metadata (struct demux_internal*,double) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_cache (struct demux_internal*) ; 
 int /*<<< orphan*/  update_final_metadata (TYPE_1__*,struct timed_metadata*) ; 

void demux_update(demuxer_t *demuxer, double pts)
{
    assert(demuxer == demuxer->in->d_user);
    struct demux_internal *in = demuxer->in;

    if (!in->threading)
        update_cache(in);

    pthread_mutex_lock(&in->lock);

    pts = MP_ADD_PTS(pts, -in->ts_offset);

    struct timed_metadata *prev = lookup_timed_metadata(in, in->last_playback_pts);
    struct timed_metadata *cur = lookup_timed_metadata(in, pts);
    if (prev != cur || in->force_metadata_update) {
        in->force_metadata_update = false;
        update_final_metadata(demuxer, cur);
        demuxer->events |= DEMUX_EVENT_METADATA;
    }

    in->last_playback_pts = pts;

    demuxer->events |= in->events;
    in->events = 0;
    if (demuxer->events & (DEMUX_EVENT_METADATA | DEMUX_EVENT_STREAMS))
        demux_update_replaygain(demuxer);
    if (demuxer->events & DEMUX_EVENT_DURATION)
        demuxer->duration = in->duration;

    pthread_mutex_unlock(&in->lock);
}