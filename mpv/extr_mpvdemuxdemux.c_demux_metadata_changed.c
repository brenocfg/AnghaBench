#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct demux_stream {TYPE_2__* tags_demux; } ;
struct demux_internal {int num_streams; int /*<<< orphan*/  lock; TYPE_1__** streams; TYPE_3__* d_thread; } ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; struct demux_internal* in; } ;
typedef  TYPE_3__ demuxer_t ;
struct TYPE_6__ {int /*<<< orphan*/  demux; } ;
struct TYPE_5__ {struct demux_stream* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ds_modify_demux_tags (struct demux_stream*) ; 
 int /*<<< orphan*/  mp_tags_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void demux_metadata_changed(demuxer_t *demuxer)
{
    assert(demuxer == demuxer->in->d_thread); // call from demuxer impl. only
    struct demux_internal *in = demuxer->in;

    pthread_mutex_lock(&in->lock);

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;
        ds_modify_demux_tags(ds);
        mp_tags_replace(ds->tags_demux->demux, demuxer->metadata);
    }

    pthread_mutex_unlock(&in->lock);
}