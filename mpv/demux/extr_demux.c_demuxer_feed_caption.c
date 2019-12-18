#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct demux_internal {int /*<<< orphan*/  lock; int /*<<< orphan*/  ts_offset; } ;
struct TYPE_7__ {int keyframe; int /*<<< orphan*/  stream; void* dts; void* pts; } ;
typedef  TYPE_2__ demux_packet_t ;
struct TYPE_6__ {struct demux_internal* in; } ;

/* Variables and functions */
 void* MP_ADD_PTS (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_packet_locked (struct sh_stream*,TYPE_2__*) ; 
 struct sh_stream* demuxer_get_cc_track_locked (struct sh_stream*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__*) ; 

void demuxer_feed_caption(struct sh_stream *stream, demux_packet_t *dp)
{
    struct demux_internal *in = stream->ds->in;

    pthread_mutex_lock(&in->lock);
    struct sh_stream *sh = demuxer_get_cc_track_locked(stream);
    if (!sh) {
        pthread_mutex_unlock(&in->lock);
        talloc_free(dp);
        return;
    }

    dp->keyframe = true;
    dp->pts = MP_ADD_PTS(dp->pts, -in->ts_offset);
    dp->dts = MP_ADD_PTS(dp->dts, -in->ts_offset);
    dp->stream = sh->index;
    add_packet_locked(sh, dp);
    pthread_mutex_unlock(&in->lock);
}