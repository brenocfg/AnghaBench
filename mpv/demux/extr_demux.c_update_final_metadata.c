#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timed_metadata {struct mp_tags* tags; scalar_t__ from_stream; } ;
struct sh_stream {scalar_t__ type; struct mp_tags* tags; int /*<<< orphan*/  attached_picture; } ;
struct mp_tags {int dummy; } ;
struct demux_internal {int num_streams; struct sh_stream* metadata_stream; struct sh_stream** streams; TYPE_1__* d_user; } ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 scalar_t__ STREAM_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_tags_merge (int /*<<< orphan*/ ,struct mp_tags*) ; 

__attribute__((used)) static void update_final_metadata(demuxer_t *demuxer, struct timed_metadata *tm)
{
    assert(demuxer == demuxer->in->d_user);
    struct demux_internal *in = demuxer->in;

    struct mp_tags *dyn_tags = NULL;

    // Often useful for audio-only files, which have metadata in the audio track
    // metadata instead of the main metadata, but can also have cover art
    // metadata (which libavformat likes to treat as video streams).
    int astreams = 0;
    int astream_id = -1;
    int vstreams = 0;
    for (int n = 0; n < in->num_streams; n++) {
        struct sh_stream *sh = in->streams[n];
        if (sh->type == STREAM_VIDEO && !sh->attached_picture)
            vstreams += 1;
        if (sh->type == STREAM_AUDIO) {
            astreams += 1;
            astream_id = n;
        }
    }

    // Use the metadata_stream tags only if this really seems to be an audio-
    // only stream. Otherwise it will happen too often that "uninteresting"
    // stream metadata will trash the actual file tags.
    if (vstreams == 0 && astreams == 1 &&
        in->streams[astream_id] == in->metadata_stream)
    {
        dyn_tags = in->metadata_stream->tags;
        if (tm && tm->from_stream)
            dyn_tags = tm->tags;
    }

    // Global metadata updates.
    if (tm && !tm->from_stream)
        dyn_tags = tm->tags;

    if (dyn_tags)
        mp_tags_merge(demuxer->metadata, dyn_tags);
}