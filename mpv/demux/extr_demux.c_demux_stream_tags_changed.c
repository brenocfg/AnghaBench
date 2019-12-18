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
struct sh_stream {struct demux_stream* ds; } ;
struct mp_tags {int dummy; } ;
struct demuxer {struct demux_internal* in; } ;
struct demux_stream {int dummy; } ;
struct demux_internal {int /*<<< orphan*/  lock; struct demuxer* d_thread; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  add_timed_metadata (struct demux_internal*,struct mp_tags*,struct sh_stream*,double) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_tags*) ; 

void demux_stream_tags_changed(struct demuxer *demuxer, struct sh_stream *sh,
                               struct mp_tags *tags, double pts)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_thread);
    struct demux_stream *ds = sh ? sh->ds : NULL;
    assert(!sh || ds); // stream must have been added

    pthread_mutex_lock(&in->lock);

    if (pts == MP_NOPTS_VALUE) {
        MP_WARN(in, "Discarding timed metadata without timestamp.\n");
    } else {
        add_timed_metadata(in, tags, sh, pts);
    }
    talloc_free(tags);

    pthread_mutex_unlock(&in->lock);
}